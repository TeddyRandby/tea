#ifndef TSandbox_DEFINED
#define TSandbox_DEFINED

#include "src/tea/screen/TApplication.hpp"
#include "build/TeaConfig.h"

typedef struct Proportional {
  Proportional(const float w, const float h):fW(w),fH(h) {}
  void operator()(TComponent& c) {
      c.setWH(fW, fH);
      c.addTitle("Proportional");
      c.setBorder(1);
  } 

  private:
  float fW;
  float fH;

} Proportional;

void borderless(TComponent &c) {
  c.addTitle("Borderless");
  c.setBorder(0); 
}

void bigMargin(TComponent &c) {
  c.setMargin(2);
}

// FOr some reason, all the components under this are
// starting offset one too many.
int main(int argc, char *argv[]) {

  // Components can be lambdas...
  auto tea = TApplication([](TComponent &app) {
    app.addLine("Press Esc to quit");
    app.addTitle(" Application");
    app.toggleDirection();
    app.setPadding(3);

    // Callabale structs...
    Proportional left = Proportional(.2,.5);
    app.render(left);

    app.render([](TComponent &section2) {
      section2.addTitle(" Section 2");

  
      // They can nest as much as you want too.

      // Or just plain functions.
      section2.render(borderless);

      // You can even use function components to modify components!
      bigMargin(section2);
    });

    Proportional right = Proportional(.3,.5);
    app.render(right);

  });

  tea.run();

  exit(0);
};

#endif
