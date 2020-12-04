#include <curses.h>
#include <iostream>
#include "TestConfig.h"

#define ITERMAX 10000

int main(int argc, char* argv[]) {
   std::cout << "hello cmake world" << std::endl;

   if (argc < 2) {
      std::cout << "Version: " << argv[0] << Test_VERSION_MAJOR << "." << Test_VERSION_MINOR << std::endl;
      std::cout << "Usage: " << argv[0] << " number" << std::endl;
   };

   long iter;
   int yi, xi;
   int y[3], x[3];
   int index;

   int maxlines, maxcols;

   // Initialize Curses

   initscr();
   cbreak();
   noecho();

   clear();

   // Initialize triangle

   maxcols = COLS - 1;
   maxlines= LINES - 1;

   y[0] = 0;
   x[0] = 0;

   y[1] = maxlines;
   x[1] = maxcols / 2;

   y[2] = 0;
   x[2] = maxcols;

   mvaddch(y[0], x[0], '0');
   mvaddch(y[1], x[1], '1');
   mvaddch(y[2], x[2], '2');

   yi =  ( (float)rand() / RAND_MAX ) * maxlines;
   xi =  ( (float)rand() / RAND_MAX ) * maxcols;

   mvaddch(yi, xi, '.'); 

   for (iter = 0; iter < ITERMAX; iter++) {
      index = ( (float)rand() / RAND_MAX ) * 3;            

      yi = (yi + y[index]) / 2;
      xi = (xi + x[index]) / 2;

      mvaddch(yi, xi, '*'); 
      refresh();
   }

   // Triangle done

   mvaddstr(maxlines, 0, "Press any key to quit.");
   
   refresh();

   // Wait for input (any key)
   getch();

   // End the ncurses window
   endwin();

   exit(0);
}
