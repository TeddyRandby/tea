#ifndef TWindow_DEFINED
#define TWindow_DEFINED

#include <TComponent.hpp>
#include <curses.h>

class TWindow {
public:
  TWindow() {
    initscr();
    noecho();

    this->fCols = COLS - 1;
    this->fRows = LINES - 1;

    clear();
  };

  ~TWindow() { endwin(); }

  void draw(const int x, const int y, const TComponent &c) {
    SizeD winSize = c.size();

    if (c.hasBorder())
      drawBorder(x, y, winSize);

    drawTitle(x + 1, y, c.title(), winSize);
    drawBody(x + c.hasBorder() + c.margin(),
               y + c.sizeHeader().y() + c.margin(), c.content(), winSize);

    SizeD offset = c.offset() + SizeD{x,y};
    for (auto &sc : c.fSubComponents) {
      draw(offset.x(), offset.y(), sc);
      if (c.dir() == TComponent::HORIZONTAL) {
        offset += {sc.size().x() + 1,0};
      } else {
        offset += {0, sc.size().y() + 1};
      }
    }
  }

  void setSize(const int cols, const int rows) {
    fCols = cols;
    fRows = rows;
  }

  SizeD size() const noexcept { return {fCols, fRows}; }
private:
  /**
   * The actual width and height of the component.
   * NOTE: This is also INCLUSIVE of the border.
   */
  int fCols = 0;
  int fRows = 0;

  void drawTitle(const int x, const int y, const std::string str, const SizeD winSize) {
    move(y, x);
    int locX, locY;
    locX = x;
    locY = y;
    const int capX = x + winSize.x();
    const int capY = y + winSize.y();

    for (char ch : str) {

      if (locX > capX) {
        locX = x;
        locY++;
        move(locY, locX);
        if (locY > capY) {
          break;
        }
      }

      if (ch == '\n') {
        locY++;
        locX = x;
        move(locY, locX);
      } else if(ch == ' ') {
        locX++;  
        move(locY, locX);
      } else {
        locX++;
        addch(ch);
      }
    }
  }

  void drawBody(const int x, const int y, const std::string str,
                  const SizeD winSize) {
    move(y, x);
    int locX, locY;
    locX = x;
    locY = y;
    const int capX = x + winSize.x();
    const int capY = y + winSize.y();

    for (char ch : str) {

      if (locX > capX) {
        locX = x;
        locY++;
        move(locY, locX);
        if (locY > capY) {
          break;
        }
      }

      if (ch == '\n') {
        locY++;
        locX = x;
        move(locY, locX);
      } else {
        locX++;
        addch(ch);
      }
    }

  }

  void drawBorder(const int x, const int y, const SizeD winSize) {

    for (int i = 0; i < winSize.x(); ++i) {
      move(y, x + i);
      addch(ACS_HLINE);
      move(y + winSize.y(), x + i);
      addch(ACS_HLINE);
    }

    for (int i = 0; i < winSize.y(); ++i) {
      move(y + i, x);
      addch(ACS_VLINE);
      move(y + i, x + winSize.x());
      addch(ACS_VLINE);
    }

    move(y, x);
    addch(ACS_ULCORNER);
    move(y, x + winSize.x());
    addch(ACS_URCORNER);
    move(y + winSize.y(), x);
    addch(ACS_LLCORNER);
    move(y + winSize.y(), x + winSize.x());
    addch(ACS_LRCORNER);
  }};
#endif
