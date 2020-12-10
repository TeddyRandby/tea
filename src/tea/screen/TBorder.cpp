#ifndef TBorder_DEFINED
#define TBorder_DEFINED

#include "TScreen.hpp"

void TScreen::drawBorder(const int x, const int y, const TComponent &c) {

  if (c.hasBorder()) {
    const SizeD w = c.size() - 1;

    for (int i = 0; i < w.x(); ++i) {
      move(y, x + i);
      addch(ACS_HLINE);
      move(y + w.y(), x + i);
      addch(ACS_HLINE);
    }

    for (int i = 0; i < w.y(); ++i) {
      move(y + i, x);
      addch(ACS_VLINE);
      move(y + i, x + w.x());
      addch(ACS_VLINE);
    }

    move(y, x);
    addch(ACS_ULCORNER);
    move(y, x + w.x());
    addch(ACS_URCORNER);
    move(y + w.y(), x);
    addch(ACS_LLCORNER);
    move(y + w.y(), x + w.x());
    addch(ACS_LRCORNER);
  };
};

#endif
