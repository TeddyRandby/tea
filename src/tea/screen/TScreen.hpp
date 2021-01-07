#ifndef TScreen_DEFINED
#define TScreen_DEFINED

#include <curses.h>
#include "../component/TComponent.hpp"

class TScreen {
public:

  TScreen() {
    initscr();
    noecho();
    resize();
    clear();
    curs_set(0);
  };

  ~TScreen() { }

  void draw(const int x, const int y, const TComponent &c) {

    if (c.fStyle.getCollapsed()) {
      drawCollapsed(x,y,c);
    } else {
      drawBorder(x, y, c);
      drawHeader(x, y, c);
      drawBody(x, y, c);

    SizeD offset = c.offset() + SizeD{x,y};
//    SizeD space = c.size()
    for (auto &sc : c.fSubComponents) {
      draw(offset.x(), offset.y(), sc);
      if (c.dir() == TStyle::Direction::HORIZONTAL) {
        offset += {sc.size().x(),0};
      } else {
        offset += {0, sc.size().y()};
      }
    }
    }

    // Rather than trying to shrink or disappear components, just find their minimum size.
    // Padding and margin should be able to shrink.


  }

  void resize() {
    getmaxyx(stdscr, fRows, fCols);
    fRows--;
    fCols--;
  }

  void setSize(const int cols, const int rows) {
    fCols = cols;
    fRows = rows;
  }

  SizeD size() const noexcept { return {fCols, fRows}; }

  void inline addPixel(const int x, const int y, const chtype ch) const {
      mvaddch(y,x,ch); 
  }

  void drawBorder(const int x, const int y, const TComponent& c) const;

  void drawBody(const int x, const int y, const TComponent& c) const;

  void drawHeader(const int x, const int y, const TComponent& c) const;

  void drawCollapsed(const int x, const int y, const TComponent& c) const;

private:

  /**
   * The actual width and height of the component.
   * NOTE: This is also INCLUSIVE of the border.
   */
  int fCols = 0;
  int fRows = 0;



};

#endif
