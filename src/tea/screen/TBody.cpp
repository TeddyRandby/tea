#ifndef TBody_DEFINED
#define TBody_DEFINED

#include "TScreen.hpp"

void TScreen::drawBody(const int x, const int y, const TComponent &c) const {
  const int startX = x + c.fStyle.offset().x();
  // Below code counts same line twice
  const int startY = y + c.fStyle.offset().y();

  SizeD w = c.size();

  int locX, locY;
  locX = startX;
  locY = startY;

  const Border b = c.fStyle.getBorder();
  const Margin m = c.fStyle.getMargin();

  chtype focused = c.focused() && b == Border{0,0,0,0} ? A_STANDOUT : A_DIM;

  const int capX = x + w.x() - b.r() - m.r();
  const int capY = y + w.y() - b.b() - m.r();

  if (startX >= capX || startY >= capY) {
    return;
  }

  for (char ch : c.body()) {

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
      addPixel(locX, locY, ch | c.fStyle.attributes() | focused);
      locX++;
    }
  };
};

#endif
