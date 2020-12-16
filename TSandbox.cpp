#ifndef TSandbox_DEFINED
#define TSandbox_DEFINED

#include "src/tea/screen/TApplication.hpp"
#include "build/TeaConfig.h"

typedef struct Proportional {
  Proportional(const float w, const float h):fW(w),fH(h) {}
  void operator()(TComponent& c) {
      c.setWH(fW, fH);
      c.addHeader(" Proportional");
      c.setBorder(1);
      c.setPadding(0);
  } 

  private:
  float fW;
  float fH;

} Proportional;

void extraBorder(TComponent &c) {
  c.addHeader("  Extra Border");
  c.setBorder({2,2,1,1}); 
}

void bigMargin(TComponent &c) {
  c.setMargin(2);
}

// FOr some reason, all the components under this are
// starting offset one too many.
int main(int argc, char *argv[]) {

  // Components can be lambdas...
  auto tea = TApplication([](TComponent &app) {
    app.addHeader(" Application");
    //app.horizontal();
    app.setMargin(0);
    app.setBorder(2);

    // Callabale structs...
    Proportional left = Proportional(.5,.3);
    app.render(left);

    app.render([](TComponent &section2) {
      section2.addHeader(" Section 2");

      // They can nest as much as you want too.
      section2.vertical();

      // Or just plain functions.
      section2.render(extraBorder);
      section2.addLine("Press (Esc) to quit");

      // You can even use function components to modify components!
      bigMargin(section2);
    });

    Proportional right = Proportional(.5,.3);
    app.render(right);

    app.setPadding(3);
  });

  tea.run();

  exit(0);
};

#endif
