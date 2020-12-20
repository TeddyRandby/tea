#ifndef TApplication_DEFINED
#define TApplication_DEFINED

#include "TScreen.hpp"
#include <set>

class TApplication : public TComponent {
public:
  /**
   * An application is the top-level component.
   * Therefore, an application's parent is itself.
   */
  TApplication(Generator gen = [](auto &) {}, std::string key="Tea") : TComponent(this, gen, key){
    TComponent::focus();
  };
  TApplication(const TApplication &app) : TComponent(this, app.fGenerator,app.fKey) {}

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
        draw();
      } else {
        if (input(key))
          draw();
      }
    }
    endwin();
  }

private:
  TScreen fScreen;

  std::set<std::string> fFocusedComponents = {fKey};

  bool focused(std::string uid) const noexcept override {
    return fFocusedComponents.count(uid) > 0;
  }

  void focus(std::string uid) noexcept override {
    if (!focused(uid))
      fFocusedComponents.insert(uid);
  }

  void unfocus(std::string uid) noexcept override {
    fFocusedComponents.erase(uid);
  }

  void draw() {
    clear();
    this->TComponent::operator=(TComponent(this, fGenerator, fKey));
    generate();
    fScreen.resize();
    fScreen.draw(0, 0, *this);
    fScreen.drawBorder(0,0,*this);
    fScreen.drawHeader(0,0,*this);
    refresh();
  }
};

#endif
