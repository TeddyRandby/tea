#ifndef TComponent_DEFINED
#define TComponent_DEFINED

#include "TContent.hpp"
#include "TVec2.hpp"
#include <iostream>
#include <assert.h>
#include <functional>
#include <string>
#include <vector>

class TComponent {
protected:
  enum Direction { VERTICAL, HORIZONTAL };
  typedef std::vector<TComponent> SubComponents;
  typedef std::function<void(TComponent&)> Generator;

public:
  /**
   * When destroyed, recursively destroy children.
   * This probably already happens, without this code.
   */
  ~TComponent() { fSubComponents.clear(); }

  /**
   * Content related methods.
   *
   * Delegate to the content object.
   * NOTE: Default arguments allow users to pad/space titles and content.
   *
   * Content is within the border and margin of a component.
   */
  std::string content() const noexcept { return fContent.content(); }
  TComponent &addLine(std::string l = "") noexcept {
    fContent.addLine(l);
    return *this;
  }

  /**
   * A Title is outside the margin of a component,
   *  and within the border (if present. )
   */
  std::string title() const noexcept { return fContent.title(); }
  TComponent &addTitle(std::string t = "") noexcept {
    fContent.addTitle(t);
    return *this;
  }

  /**
   * Adds a child component with the given generator.
   * Returns a reference to the created component.
   */
  TComponent &addComponent(const Generator gen) noexcept {
    fSubComponents.emplace_back(TComponent(this, gen));
    return *this;
  }

  /**
   * A border is drawn around the edge of the whole container.
   * NOTE: Titles are drawn over the top border.
   */
  bool hasBorder() const noexcept { return fBorder; }
  TComponent &toggleBorder() noexcept {
    fBorder = !fBorder;
    return *this;
  }

  /**
   * A margin is the space between the edge of the container and the content.
   * If a border is present, this does NOT include the border.
   */
  int margin() const noexcept { return fMargin; }
  TComponent &setMargin(const int m) noexcept {
    fMargin = m;
    return *this;
  }

  /**
   * Direction controls the way content and subComponents are stacked.
   */
  Direction dir() const noexcept { return fDir; }
  TComponent &toggleDirection() noexcept {
    if (fDir == Direction::HORIZONTAL) {
      fDir = Direction::VERTICAL;
    } else {
      fDir = Direction::HORIZONTAL;
    }
    return *this;
  }

  /**
   * Control the relative (to parent) width and height of the component.
   */
  TComponent &setWidth(const float w) noexcept {
    if (w <= 0) {
      fWidth = 0;
    } else if (w >= 1) {
      fWidth = 1;
    } else {
      fWidth = w;
    }
    return *this;
  }

  TComponent &setHeight(const float h) noexcept {
    if (h <= 0) {
      fHeight = 0;
    } else if (h >= 1) {
      fHeight = 1;
    } else {
      fHeight = h;
    }
    return *this;
  }

  TComponent &setWH(const SizeN wh) noexcept {
    setWidth(wh.x());
    setHeight(wh.y());
    return *this;
  }

  TComponent &setWH(const float w, const float h) noexcept {
    setWidth(w);
    setHeight(h);
    return *this;
  }

  AbsPos absPos() const noexcept { return {fAbsX, fAbsY}; }

  /**
   * Run the user-provided Generator.
   * Flush previous data.
   * This is useful for testing, without rendering to a screen.
   * Update these components IN PLACE.
   */
  void generate() noexcept {
    fGenerator(*this);
    for (TComponent& c : fSubComponents) {
      c.generate();
    }
  }

  /**
   * Calculate the size available for this component.
   * Needs to include childrens sizes.
   *
   * Separate into calculating width and height.
   * At this point, depending on the direction this child is being
   * drawn in, either the w or the h of the component is known.
   * This means that the other val is deterministic.
   * NOTE: This method is virtual because it is overridden by the application
   * component.
   */
  virtual SizeD size() const {
    const auto inner = fParent->size() - fParent->sizeContent();
    const auto direction = fParent->dir();

    // Both width and height are fixed relative to parent.
    if (fWidth >= 0 && fHeight >= 0) {
      return SizeD(fWidth * (float)inner.x(), fHeight * (float)inner.y());
    }

    int w, h;
    if (direction == Direction::HORIZONTAL) {
      /**
       * height is determined to be inner.y();
       * width still depends on content and children.
       * width = max(content + sum children width, title)
       * There will be wrapping during rendering, but as far
       * as calculating size goes, we can stop here.
       */
      h = inner.y();
      w = width();
    } else {
      /**
       * width is determined to be inner.x();
       * height still depends on content and children.
       * height = max(content + sum children height, title)
       * There will be wrapping during rendering, but as far
       * as calculating size goes, we can stop here.
       */
      w = inner.x();
      h = height();
    }
    return SizeD(w, h);
  }

protected:
  /**
   * A TComponent cannot have a nullptr for a parent.
   */
  TComponent(TComponent *p, Generator gen) : fGenerator(gen) {
    assert(p);
    fParent = p;
  }
private:
  /**
   * A boolean to toggle a border on and off.
   */
  bool fBorder = true;

  /**
   * The discrete amount of space (chars) between content and border.
   * NOTE: If no border is present, then margin spreads into where
   *    a border would be.
   */
  int fMargin = 0;

  /**
   *
   */
  TComponent *fParent = nullptr;
  Direction fDir = Direction::VERTICAL;
  SubComponents fSubComponents = {};

  /**
   * The render function supplied by the user.
   * This function prepares the component to actually be drawn
   * by manipulating its content and children.
   * NOTE: Often a lambda, but uses std::function so any callable object will
   * do. NOTE: tea will always be the component calling the render function.
   *
   */
  Generator fGenerator;

  /*
   * The object that manages teh title and content of hte component.
   */
  TContent fContent;

  /**
   * Width and height are normalized on the interval [0...1]
   * A value of -1 implies component will fill its container
   *  responsively. This is the default behavior.
   *
   * NOTE: Struct SizeN(ormalized) is for getting values.
   * NOTE: This is INCLUSIVE of the border.
   * EX:
   *   |a| === aaa
   */
  float fWidth = -1;
  float fHeight = -1;

  /**
   * X and Y position of the top left corner of the component.
   */
  int fAbsX = 0;
  int fAbsY = 0;

  /**
   * Reset the Component to be generated again.
   * NOTE: Clearing the children is preferred to calling their flush()
   * methods because children are added in the generate() call.
   */
  void flush() noexcept {
    fContent.flush();
    fSubComponents.clear();
  }

  /**
   * Delegated helper getters.
   * ContentSize here INCLUDES border and margin.
   * Returns the size of the content given a width.
   * A w of -1 turns off text wrapping.
   */
  SizeD sizeContent() const {
    return fContent.sizeContent() + (2 * hasBorder()) + (margin());
  }

  /**
   */
  SizeD sizeTitle() const { return fContent.sizeTitle() - SizeD(0,hasBorder()); }

  /**
   * Recursively calculate the width that this component
   * and all children components will fill.
   * NOTE: This does not do any wrapping.
   */
  int width() const {
    int w = sizeContent().x();
    for (auto c : fSubComponents) {
      w += c.width();
    }
    return std::max<int>(sizeTitle().x(), w);
  }

  /**
   * Recursively calculate the height that this component
   * and all children components will fill.
   * NOTE: This does not do any wrapping.
   */
  int height() const {
    int h = sizeContent().y() + sizeTitle().y();
    for (auto c : fSubComponents) {
      h += c.height();
    }
    return h;
  }};
#endif
