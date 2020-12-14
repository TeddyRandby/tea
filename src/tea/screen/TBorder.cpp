#ifndef TBorder_DEFINED
#define TBorder_DEFINED

#include "TScreen.hpp"

void TScreen::drawBorder(const int x, const int y, const TComponent &c) {

    const Border b = c.fStyle.getBorder();

    SizeD w = c.size();

    const Margin m = c.fStyle.getMargin();

    const int startX = x + m.l();
    const int startY = y + m.t();
    const int endX = x + w.x() - m.r();
    const int endY = y + w.y() - m.b();

    for (int i = 0; i < b.t(); i++) {
      for (int j = startX + i; j < endX - i; j++)
        addPixel(j, startY + i, ACS_HLINE);
    }

    for (int i = 0; i < b.b(); i++) {
      for (int j = startX + i; j < endX - i; j++)
        addPixel(j, endY - i, ACS_HLINE);
    }

    for (int i = 0; i < b.l(); i++) {
      for (int j = startY + i; j < endY - i; j++)
        addPixel(startX + i, j, ACS_VLINE);
    }

    for (int i = 0; i < b.r(); i++) {
      for (int j = startY + i; j < endY - i; j++)
        addPixel(endX - i, j, ACS_VLINE);
    }

    for (int i = 0; i < b.l(); ++i) {
      if (i <= b.t())
        addPixel(startX + i, startY + i , ACS_ULCORNER);
      if (i <= b.b())
        addPixel(startX + i, endY - i , ACS_LLCORNER);
    }

    for (int i = 0; i < b.r(); ++i) {
      if (i <= b.t())
        addPixel(endX - i, startY + i, ACS_URCORNER);
      if (i <= b.b())
        addPixel(endX - i, endY - i , ACS_LRCORNER);
    }
};

#endif
