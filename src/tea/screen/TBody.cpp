#ifndef TBorder_DEFINED
#define TBorder_DEFINED

#include "TScreen.hpp"

void TScreen::drawBody(const int x, const int y, const TComponent &c) {
  const int startX = x + c.hasBorder() + c.margin();
  const int startY = y + c.sizeHeader().y() + c.margin();
  move(startX, startY);

  const SizeD w = c.size();

  int locX, locY;
  locX = x;
  locY = y;

  const int capX = x + w.x();
  const int capY = y + w.y();

  for (char ch : c.content()) {

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
    } else {
      locX++;
      addch(ch);
    }
  };
};

#endif
