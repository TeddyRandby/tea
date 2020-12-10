#ifndef TBorder_DEFINED
#define TBorder_DEFINED

#include "TScreen.hpp"

void TScreen::drawHeader(const int x, const int y, const TComponent &c) {
  const int startX = x + 1;
  const int startY = y;
  move(startY, startX);

  const SizeD w = c.size();

  int locX, locY;
  locX = x;
  locY = y;

  const int capX = x + w.x();
  const int capY = y + w.y();

  for (char ch : c.title()) {

    if (locX > capX) {
      locX = x;
      locY++;
      move(locY, locX);
      if (locY > capY) {
        break;
      }
    }

    if (ch == '\n') {
      locY++;
      locX = x;
      move(locY, locX);
    } else if(ch == ' ') {
      locX++;  
      move(locY, locX);
    } else {
      locX++;
      addch(ch);
    }
  }
}

#endif
