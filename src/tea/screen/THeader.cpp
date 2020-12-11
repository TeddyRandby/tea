#ifndef TBorder_DEFINED
#define TBorder_DEFINED

#include "TScreen.hpp"

void TScreen::drawHeader(const int x, const int y, const TComponent &c) {
  const Margin m = c.fStyle.getMargin();
  const int startX = x + m.l();
  const int startY = y + m.t();

  const SizeD w = c.size();

  int locX, locY;
  locX = startX;
  locY = startY;

  const int capX = startX + w.x() - m.r();

  for (char ch : c.title()) {

    if (locX > capX || ch == '\n') {
      break;
    } else if(ch == ' ') {
      locX++;  
    } else {
      addPixel(locX,locY,ch);
      locX++;
    }

  }
}

#endif
