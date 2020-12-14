#ifndef TComponent_DEFINED
#define TComponent_DEFINED

#include "../utils/TVec.hpp"
#include "TContent.hpp"
#include "TStyle.hpp"
#include <assert.h>
#include <curses.h>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

class TComponent {

  /**
   * The screen class needs access in order to draw components.
   */
  friend class TScreen;
  friend class TApplication;

protected:
  typedef std::function<void(TComponent &)> Generator;
  enum Direction { VERTICAL, HORIZONTAL };
  typedef std::vector<TComponent> SubComponents;

  /**
   * A TComponent cannot have a nullptr for a parent.
   */
  TComponent(TComponent *p, Generator gen, TStyle styles=TStyle()) : fGenerator(gen), fStyle(styles) {
    assert(p);
    fParent = p;
  }

public:
  ~TComponent() {}

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
  TComponent &render(const Generator gen) noexcept {
    fSubComponents.emplace_back(TComponent(this, gen, fStyle));
    return *this;
  }

  /**
   * A border is drawn around the edge of the whole container.
   * NOTE: Titles are drawn over the top border.
   */
  TComponent &setBorder(const int b) noexcept {
    fStyle.setBorder(b);
    return *this;
  }
  TComponent &setBorder(const Border &b) noexcept {
    fStyle.setBorder(b);
    return *this;
  }
  Border getBorder() const noexcept {
    return fStyle.getBorder();
  }

  /**
   * A margin is the space between a component and sibling components.
   * If a border is present, this does NOT include the border.
   */
  TComponent &setMargin(const int m) noexcept {
    fStyle.setMargin(m);
    return *this;
  }

  TComponent &setMargin(const Margin &m) noexcept {
    fStyle.setMargin(m);
    return *this;
  }
  Margin getMargin() const noexcept {
    return fStyle.getMargin();
  }
  /**
   * Padding is the space between border and content.
   * If a border is present, this does NOT include the border.
   */
  TComponent &setPadding(const int p) noexcept {
    fStyle.setPadding(p);
    return *this;
  }

  TComponent &setPadding(const Padding &p) noexcept {
    fStyle.setPadding(p);
    return *this;
  }
  Padding getPadding() const noexcept {
    return fStyle.getPadding();
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
      fWidthN = 0;
    } else if (w >= 1) {
      fWidthN = 1;
    } else {
      fWidthN = w;
    }
    return *this;
  }

  TComponent &setHeight(const float h) noexcept {
    if (h <= 0) {
      fHeightN = 0;
    } else if (h >= 1) {
      fHeightN = 1;
    } else {
      fHeightN = h;
    }
    return *this;
  }

  TComponent &setWH(const float w, const float h) noexcept {
    setWidth(w);
    setHeight(h);
    return *this;
  }

  /**
   * Control the relative (to parent) width and height of the component.
   */
  TComponent &setWidth(const int w) noexcept {
    if (w <= 0) {
      fWidthD = 0;
    } else {
      fWidthD = w;
    }
    return *this;
  }

  TComponent &setHeight(const int h) noexcept {
    if (h <= 0) {
      fHeightD = 0;
    } else {
      fHeightD = h;
    }
    return *this;
  }

  TComponent &setWH(const int w, const int h) noexcept {
    setWidth(w);
    setHeight(h);
    return *this;
  }

  /**
   * Run the user-provided Generator.
   * Flush previous data.
   * This is useful for testing, without rendering to a screen.
   * Update these components IN PLACE.
   */
  void generate() noexcept {
    fGenerator(*this);
    for (TComponent &c : fSubComponents) {
      c.generate();
    }

    cachedSize = size();
    cachedOffset = offset();
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
   * This needs to shrink margin and padding if necessary
   */
  virtual SizeD size() const {
    if (cachedSize != SizeD(-1, -1))
      return cachedSize;

    const auto inner = fParent->inner();
    const auto direction = fParent->dir();

    int w, h;

    // Fill the parent container depending on its direction.
    if (direction == Direction::HORIZONTAL) {
      h = inner.y();
      w = width();
    } else {
      w = inner.x();
      h = height();
    }

    // If a relative width or height is specified, override with that.
    if (fWidthN >= 0) {
      w = fWidthN * (float)inner.x();
    }

    if (fHeightN >= 0) {
      h = fHeightN * (float)inner.y();
    }

    // If an explicit width or height is specified, override with that.
    if (fWidthD >= 0) {
      w = fWidthD;
    }

    if (fHeightD >= 0) {
      h = fHeightD;
    }
     
    const SizeD min = minimumSize();
    return SizeD(std::max<int>(w, min.x()), std::max<int>(h, min.y()));
  }

  /**
   * Minimum size excludes padding and margin.
   */
  SizeD minimumSize() const {
    SizeD subSize = {0,0};
    for (auto &c : fSubComponents) {
      subSize += c.minimumSize();
    }
    int x,y;
    x = std::max<int>({subSize.x(), sizeBody().x(), sizeHeader().x()});
    y = std::max<int>({subSize.y(), sizeBody().y(), sizeHeader().y()});
    return SizeD(x,y) + fStyle.size();
  }

  /**
   * Size of container remaining to draw children.
   */
  SizeD inner() const {
    return size() - sizeMPB() - sizeBody();
  }

  /**
   * Return the offset relative to this component where drawing the first child
   * begins. If the offset has already been calculated, just return the cached
   * value.
   */
  SizeD offset() const {
    if (cachedOffset != Offset(-1, -1))
      return cachedOffset;

    auto pad = fStyle.offset();
    int offX, offY;
    if (dir() == Direction::HORIZONTAL) {
      offX = sizeBody().x() + pad.x();
      offY = sizeHeader().y() + pad.y();
    } else {
      offX = pad.x();
      offY = sizeBody().y() + pad.y();
    }
    return Offset(offX, offY);
  }

private:
  /**
   *
   */
  SizeD cachedSize = SizeD(-1, -1);

  /**
   *
   */
  Offset cachedOffset = Offset(-1, -1);

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
   * TContent manages the header and body (text).
   */
  TContent fContent;

  /*
   * TStyle manages the appearance, border, margin, and padding.
   */
  TStyle fStyle;

  /**
   * WidthN and HeightN are normalized on the interval [0...1]
   * A value of -1 implies component will fill its container
   *  responsively. This is the default behavior.
   *
   * NOTE: This is INCLUSIVE of the border.
   * EX:
   *   |a| === aaa
   */
  float fWidthN = -1;
  float fHeightN = -1;

  /**
   * WidthD and HeightD are the exact width and height of the
   * component, in characters.
   * This has the highest specification priority.
   */
  int fWidthD = -1;
  int fHeightD = -1;

  /**
   * Delegated helper getters.
   * ContentSize here INCLUDES border and margin.
   * Returns the size of the content given a width.
   */
  SizeD sizeBody() const { return fContent.sizeContent(); }

  SizeD sizeTitle() const { return fContent.sizeTitle(); }

  /**
   * Returns the size of margin + border + padding.
   */
  SizeD sizeMPB() const { return fStyle.size(); }

  SizeD sizeHeader() const {
    if (sizeTitle().y() > 0) {
      return sizeTitle() - fStyle.hasBorder();
    } else {
      return {0, fStyle.hasBorder()};
    }
  }

  /**
   * Recursively calculate the width that this component
   * and all children components will fill.
   * NOTE: This does not account for any wrapping.
   */
  int width() const {
    int w = sizeBody().x() + sizeMPB().x();
    for (auto &c : fSubComponents) {
      w += c.width();
    }
    return std::max<int>(sizeTitle().x(), w);
  }

  /**
   * Recursively calculate the height that this component
   * and all children components will fill.
   * NOTE: This does account for any wrapping.
   * NOTE: Because the title is IN the border (if the border is present)
   *  This has to be accounted for in order to not count the border twice.
   */
  int height() const {
    int h = sizeBody().y() + sizeHeader().y() + sizeMPB().y();
    for (auto &c : fSubComponents) {
      h += c.height();
    }
    return h;
  }
};
#endif
