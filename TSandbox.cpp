#ifndef TSandbox_DEFINED
#define TSandbox_DEFINED

#include "build/TeaConfig.h"
#include "src/tea/screen/TApplication.hpp"
#include "src/tea/component/TCheckbox.hpp"
#include <iostream>

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
  c.addLine("I have extra border.");
  c.addHeader("  Extra Border");
  c.setBorder({2, 2, 1, 1});
}

void bigMargin(TComponent &c) { c.setMargin(2); }

class TeaExample : public TApplication {
  public:
  TeaExample(): TApplication(
    [&](TComponent &app) {

    app.onInput([this](int key) {
      if (key == 104) {
        isVertical = false;
        extraTitle = "Horizontal";
      }
      if (key == 118) {
        isVertical = true;
        extraTitle = "Vertical";
      }
    });

    if (isVertical) {
      app.vertical();
    } else {
      app.horizontal();
    }

    app.addHeader(" Application ");
    app.addHeader(this->extraTitle);
    app.setMargin(0);

    // Callabale structs...
    Proportional left = Proportional(.5, .2);
    app.render("Left", left);

    app.render("Margin", [&](TComponent &section2) {
      section2.addHeader(" Section 2");

      // They can nest as much as you want too.
      section2.vertical();

      section2.render("sample", [](TComponent &c){
       c.addLine("Here is some helpful text."); 
      });

      // Or just plain functions.
      section2.render("Border1", extraBorder);
      section2.render("Border2", extraBorder);
      section2.render("Border3", extraBorder);
      section2.addLine("Press (Esc) to quit");

      TCheckbox chbx = TCheckbox(this->chbox,"Here is a checkbox. Toggle w spc");
      section2.render("checkbox", chbx);

      section2.onInput([&](int key) {
        if (key == 32) {
         this->chbox = !this->chbox;
         return true;
        }
        return false;
      });
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
  bool chbox = false;
};

int main(int argc, char *argv[]) {
  TeaExample().run();
  exit(0);
};

#endif
