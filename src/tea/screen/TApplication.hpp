#ifndef TApplication_DEFINED
#define TApplication_DEFINED

#include "TScreen.hpp"

class TApplication : public TComponent {
public:
  /**
   * An application is the top-level component.
   * Therefore, an application's parent is itself.
   */
  TApplication(Generator gen = [](auto &) {}) : TComponent(this, gen){};
  TApplication(const TApplication &app) : TComponent(this, app.fGenerator) {}

  ~TApplication(){};

  /**
   * Calculate the size of this component.
   * The size of this container is always the screen size.
   */
  SizeD size() const noexcept override { return fScreen.size(); }

  /**
   * Manually set the width and height of the application.
   */
  TApplication &setSize(const int w, const int h) noexcept {
    fScreen.setSize(w, h);
    return *this;
  }

  /**
   * Enter an input loop.
   */
  void run() {
    // Initial draw
    draw();

    int key;
    while ((key = getch()) != 27) {
      if (key == KEY_RESIZE) {
        clear();
        // Redraw on resize
        draw();
        refresh();
      }
    }

    endwin();
  }

private:
  TScreen fScreen;

  void draw() {
    clear();
    this->TComponent::operator=(TComponent(this, fGenerator));
    generate();
    fScreen.resize();
    fScreen.draw(0, 0, *this);
    // Hack to draw the border of the final app on over after sub components are drawn.
    fScreen.drawBorder(0,0,*this);
    refresh();
  }
};

#endif
