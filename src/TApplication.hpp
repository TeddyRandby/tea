#ifndef TApplication_DEFINED
#define TApplication_DEFINED

#include "TComponent.hpp"
#include "TVec2.hpp"
#include <curses.h>

class TApplication : public TComponent {
  
  public:
  
  /**
   * An application is a top-level component.
   * Therefore, an application's parent is itself.
   * The curses bool is a temporary solution to curses breaking unit tests.
   */
  TApplication(Generator gen, bool test=true, int cols=400, int rows=200): TComponent(this, gen) {
    if (!test) {
        initscr();
        noecho();

        this->fCols = COLS;
        this->fRows = LINES;

        clear();
    } else {
        this->fCols = cols;
        this->fRows = rows;
    }
  };

  ~TApplication() {};

  /**
   * Calculate the size of this component.
   * The size of this container is always the screen size.
   */
  SizeD size() const override {
      return screen();
  }


  private:

  SizeD screen() const {return {fCols, fRows};}

  /**
   * The actual width and height of the component.
   * NOTE: This is also INCLUSIVE of the border.
   * NOTE: Struct SizeD(iscrete) is for getting values.
   */
  int fCols = 0;
  int fRows = 0;

};

#endif
