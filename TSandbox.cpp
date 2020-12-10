#ifndef TSandbox_DEFINED
#define TSandbox_DEFINED

#include "src/tea/component/TApplication.hpp"
#include "build/TeaConfig.h"

typedef struct Proportional {
  Proportional(const float w, const float h):fW(w),fH(h) {}
  void operator()(TComponent& c) {
      c.setWH({fW, fH});
      c.addTitle("Proportional");
  } 

  private:
  float fW;
  float fH;

} Half;

void borderless(TComponent &c) {
  c.addTitle("Borderless");
  c.toggleBorder(); 
}

int main(int argc, char *argv[]) {

  // Components can be lambdas...
  auto tea = TApplication([](TComponent &app) {
    app.addTitle("Application");
    app.addTitle(" Press esc to quit.");

    // Callabale structs...
    Proportional half = Proportional(.5,.5);
    app.addComponent(half);

    app.addComponent([](TComponent &section2) {
      section2.addTitle("I am section two");

      // Or just plain functions.
      section2.addComponent(borderless);
    });

    // I can even reuse this function to affect another component.
    borderless(app);
  });

  tea.run();

  exit(0);
};

#endif
