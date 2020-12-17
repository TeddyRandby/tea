#ifndef TCollapsed_DEFINED
#define TCollapsed_DEFINED

#include "TScreen.hpp"

void TScreen::drawCollapsed(const int x, const int y, const TComponent &c) const {
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

  for (int i = startX; i < capX; i++) {
    addPixel(i,locY,ACS_HLINE);    
  }

  for (const char ch : c.header()) {
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
