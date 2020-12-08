#ifndef TSandbox_DEFINED
#define TSandbox_DEFINED

#include <curses.h>
#include <iostream>
#include "TeaConfig.h"

#include "src/TApplication.hpp"

int main(int argc, char* argv[]) {
   
   auto tea = TApplication([](auto &app){
     app.addLine("Test Line");
     app.addTitle("Test title");
   });

   tea.generate();

   endwin();

   exit(0);
};

#endif
