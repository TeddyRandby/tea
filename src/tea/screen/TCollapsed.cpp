#ifndef TCollapsed_DEFINED
#define TCollapsed_DEFINED

#include "TScreen.hpp"

void TScreen::drawCollapsed(const int x, const int y,
                            const TComponent &c) const {
  const Margin m = c.fStyle.getMargin();
  const Border b = c.fStyle.getBorder();
  const int startX = x + m.l();
  const int startY = y + m.t();

  SizeD w = c.size();

  int locX, locY;
  locX = startX;
  locY = startY;

  chtype focused = c.focused() ? A_STANDOUT : A_DIM;

  if (c.dir() == TStyle::Direction::VERTICAL) {

    const int capX = x + w.x() - m.r() - b.r();

    if (startX >= capX) {
      return;
    }


    for (int i = startX; i < capX; i++) {
      addPixel(i, locY, ACS_HLINE | focused);
    }

    for (const char ch : c.header()) {
      if (locX > capX || ch == '\n') {
        break;
      } else if (ch == ' ') {
        locX++;
      } else {
        addPixel(locX, locY, ch | focused);
        locX++;
      }
    }

  } else {

    const int capY = y + w.y() - m.b() - b.b();

    if (startY >= capY) {
      return;
    }

    for (int i = startY; i < capY; i++) {
      addPixel(locX, i, ACS_VLINE | focused);
    }
    
  }

}

#endif
