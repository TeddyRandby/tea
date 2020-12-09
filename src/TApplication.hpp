#ifndef TApplication_DEFINED
#define TApplication_DEFINED


#include <TComponent.hpp>
#include <TWindow.hpp>

class TApplication : public TComponent {
  
  public:
  
  /**
   * An application is a top-level component.
   * Therefore, an application's parent is itself.
   * The curses bool is a temporary solution to curses breaking unit tests.
   */
  TApplication(Generator gen=[](auto&){}): TComponent(this, gen) {};

  ~TApplication() {};

  /**
   * Calculate the size of this component.
   * The size of this container is always the screen size.
   */
  SizeD size() const override {
      return fWindow.size();
  }

  /**
   * Manually set the width and height of the application.
   */
   TApplication &setSize(const int w, const int h) noexcept {
    fWindow.setSize(w,h);
    return *this;
   }

   void draw() {
     fWindow.draw(0,0,*this);     
   }

  private:

  TWindow fWindow;

};

#endif
