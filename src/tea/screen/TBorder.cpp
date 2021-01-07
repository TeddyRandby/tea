#ifndef TBorder_DEFINED
#define TBorder_DEFINED

#include "TScreen.hpp"

void TScreen::drawBorder(const int x, const int y, const TComponent &c) const {

    const Border b = c.fStyle.getBorder();

    SizeD w = c.size();

    const Margin m = c.fStyle.getMargin();

    const int startX = x + m.l();
    const int startY = y + m.t();
    const int endX = x + w.x() - m.r()-1;
    const int endY = y + w.y() - m.b()-1;

    chtype focused = c.focused() ? A_STANDOUT : A_DIM;


    for (int i = 0; i < b.t(); i++) {
      for (int j = startX; j < endX; j++)
        addPixel(j, startY + i, ACS_HLINE | c.fStyle.attributes() | focused);
    }

    for (int i = 0; i < b.b(); i++) {
      for (int j = startX; j < endX; j++)
        addPixel(j, endY - i, ACS_HLINE | c.fStyle.attributes() | focused);
    }

    for (int i = 0; i < b.l(); i++) {
      for (int j = startY; j < endY; j++)
        addPixel(startX + i, j, ACS_VLINE | c.fStyle.attributes() | focused);
    }

    for (int i = 0; i < b.r(); i++) {
      for (int j = startY; j < endY; j++)
        addPixel(endX - i, j, ACS_VLINE | c.fStyle.attributes() | focused);
    }

    for (int i = 0; i < b.l(); ++i) {
      if (i < b.t())
        addPixel(startX + i, startY + i , ACS_ULCORNER | c.fStyle.attributes() | focused);
      if (i < b.b())
        addPixel(startX + i, endY - i , ACS_LLCORNER | c.fStyle.attributes() | focused);
    }

    for (int i = 0; i < b.r(); ++i) {
      if (i < b.t())
        addPixel(endX - i, startY + i, ACS_URCORNER | c.fStyle.attributes() | focused);
      if (i < b.b())
        addPixel(endX - i, endY - i , ACS_LRCORNER | c.fStyle.attributes() | focused);
    }
};

#endif
