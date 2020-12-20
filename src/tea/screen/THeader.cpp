#ifndef THeader_DEFINED
#define THeader_DEFINED

#include "TScreen.hpp"

void TScreen::drawHeader(const int x, const int y, const TComponent &c) const {
  const Margin m = c.fStyle.getMargin();
  const Border b = c.fStyle.getBorder();
  const int startX = x + m.l();
  const int startY = y + m.t();

  SizeD w = c.size();

  int locX, locY;
  locX = startX;
  locY = startY;

  const int capX = x + w.x() - m.r() - b.r();

  if (startX >= capX) {
    return;
  }

  chtype focused = c.focused() ? A_BOLD | A_STANDOUT : A_DIM;

  for (const char ch : c.header()) {

    if (locX > capX || ch == '\n') {
      break;
    } else if(ch == ' ') {
      locX++;  
    } else {
      addPixel(locX,locY,ch | c.fStyle.attributes() | focused);
      locX++;
    }

  }
}

#endif
