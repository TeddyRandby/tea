#ifndef TScreen_DEFINED
#define TScreen_DEFINED

#include <curses.h>
#include "../component/TComponent.hpp"
#include <iostream>

class TScreen {
public:

  TScreen() {
    initscr();
    noecho();
    resize();
    clear();
  };

  ~TScreen() { }

  void draw(const int x, const int y, const TComponent &c) {

    drawBorder(x, y, c);
    drawHeader(x, y, c);
    drawBody(x, y, c);

    SizeD offset = c.offset() + SizeD{x,y};
    for (auto &sc : c.fSubComponents) {
      draw(offset.x(), offset.y(), sc);
      if (c.dir() == TComponent::HORIZONTAL) {
        offset += {sc.size().x(),0};
      } else {
        offset += {0, sc.size().y()};
      }
    }

  }

  void resize() {
    getmaxyx(stdscr, fRows, fCols);
  }

  void setSize(const int cols, const int rows) {
    fCols = cols;
    fRows = rows;
  }

  SizeD size() const noexcept { return {fCols, fRows}; }

  void inline addPixel(const int x, const int y, const chtype ch) {
      mvaddch(y,x,ch); 
  }

private:

  /**
   * The actual width and height of the component.
   * NOTE: This is also INCLUSIVE of the border.
   */
  int fCols = 0;
  int fRows = 0;

  void drawBorder(const int x, const int y, const TComponent& c);

  void drawBody(const int x, const int y, const TComponent& c);

  void drawHeader(const int x, const int y, const TComponent& c);


};

#endif
