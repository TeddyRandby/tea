#ifndef TBorder_DEFINED
#define TBorder_DEFINED

#include "TScreen.hpp"
#include <iostream>

void TScreen::drawBorder(const int x, const int y, const TComponent &c) {

  if (c.fStyle.hasBorder()) {
    const SizeD w = c.size() - 1;
    const Margin m = c.fStyle.getMargin();
    const int startX = x + m.l();
    const int startY = y + m.t();
    const int endX = x + w.x() - m.r();
    const int endY = y + w.y() - m.b();

    for (int i = startX; i < endX; ++i) {
      addPixel(i, startY, ACS_HLINE);
      addPixel(i, endY, ACS_HLINE);
    }

    for (int i = startY; i < endY; ++i) {
      addPixel(startX, i, ACS_VLINE);
      addPixel(endX, i, ACS_VLINE);
    }

    addPixel(startX, startY , ACS_ULCORNER);
    addPixel(endX, startY, ACS_URCORNER);
    addPixel(startX, endY , ACS_LLCORNER);
    addPixel(endX, endY , ACS_LRCORNER);
  };
};

#endif
