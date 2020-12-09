#ifndef TSandbox_DEFINED
#define TSandbox_DEFINED

#include <TApplication.hpp>
#include "TComponent.hpp"
#include "TeaConfig.h"


int main(int argc, char* argv[]) {
  
  initscr();
  addch('0');

  auto tea = TApplication([](TComponent& app){
    app.addTitle("Application");
    app.addLine("Hello World");
    app.addLine("Here is some content.");

    app.addComponent([](TComponent& section) {
      section.setWH({.5,.5}).toggleDirection(); 
      section.addLine("I'm horizontal");

      section.addComponent([](TComponent& right) {
        right.addTitle("right"); 
      });
    });

    app.addComponent([](TComponent& section2) {
      section2.addTitle("I am section two");      

      section2.addComponent([](TComponent& bottom) {
        bottom.addTitle("bottom"); 
      });
    });

  });

    tea.generate();
    tea.draw();

    getch();
    endwin();

    exit(0);
};

#endif
