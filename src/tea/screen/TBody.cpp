#ifndef TBorder_DEFINED
#define TBorder_DEFINED

#include "TScreen.hpp"

void TScreen::drawBody(const int x, const int y, const TComponent &c) {
  const int startX = x + c.fStyle.offset().x();
  const int startY = y + c.sizeHeader().y() + c.fStyle.offset().y();

  const SizeD w = c.size();

  int locX, locY;
  locX = startX;
  locY = startY;

  const int capX = startX + w.x();
  const int capY = startY + w.y();

  for (char ch : c.content()) {

    if (locX > capX) {
      locX = startX;
      locY++;
      if (locY > capY) {
        break;
      }
    }

    if (ch == '\n') {
      locY++;
      locX = startX;
    } else {
      addPixel(locX, locY, ch);
      locX++;
    }
  };
};

#endif
