#ifndef TSandbox_DEFINED
#define TSandbox_DEFINED

#include "build/TeaConfig.h"
#include "src/tea/screen/TApplication.hpp"

typedef struct Proportional {
  Proportional(const float w, const float h) : fW(w), fH(h) {}
  void operator()(TComponent &c) {
    c.setWH(fW, fH);
    c.addHeader(" Proportional");
    c.setBorder(1);
    c.setPadding(0);

    if (fH < .3f) {
      c.collapse();
    }
  }
private:
  float fW;
  float fH;

} Proportional;

void extraBorder(TComponent &c) {
  c.addHeader("  Extra Border");
  c.setBorder({2, 2, 1, 1});}

void bigMargin(TComponent &c) { c.setMargin(2); }

void makeDim(TComponent &c) { c.onDim(); }

class TeaExample : public TApplication {
  public:
  TeaExample(): TApplication(
    [&](TComponent &app) {
    app.addHeader(" Application ");
    app.addHeader(this->extraTitle);
    app.setMargin(0);


    app.onInput([&](int key) {
      if (key == 104) {
        isVertical = false;
        this->extraTitle = "Horizontal";
      }
      if (key == 118) {
        isVertical = true;
        this->extraTitle = "Vertical";
      }
    });

    if (isVertical) {
      app.vertical();
    } else {
      app.horizontal();
    }

    // Callabale structs...
    Proportional left = Proportional(.5, .2);
    app.render("Left", left);

    app.render("Margin", [](TComponent &section2) {
      section2.addHeader("Section 2");

      // They can nest as much as you want too.
      section2.vertical();

      makeDim(section2);

      // Or just plain functions.
      section2.render("Border", extraBorder);
      section2.addLine("Press (Esc) to quit");

      // You can even use function components to modify components!
      bigMargin(section2);
    });

    Proportional right = Proportional(.5, .3);
    app.render("Right", right);

    app.setPadding(3);
  }
  ){};

  //mem vars
  std::string extraTitle = "Vertical";
  bool isVertical = true;
};

int main(int argc, char *argv[]) {
  TeaExample().run();
  exit(0);
};

#endif
