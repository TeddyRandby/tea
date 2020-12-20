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
   * TApplicatoin class needs access in order to re-initialize its base class.
   */
  friend class TScreen;
  friend class TApplication;

protected:
  typedef std::function<void(TComponent &)> Generator;
  typedef std::vector<TComponent> SubComponents;

  /**
   * A TComponent cannot have a nullptr for a parent.
   */
  TComponent(TComponent *p, Generator gen, std::string key,  TStyle styles = TStyle())
      : fGenerator(gen), fStyle(styles), fKey(key) {
    assert(p);
    fParent = p;
    fIndex = p->fSubComponents.size();
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
  std::string body() const noexcept { return fContent.body(); }
  TComponent &addLine(std::string l = "") noexcept {
    fContent.addLine(l);
    return *this;
  }

  /**
   * A Header is a single line of text outside the padding of a component,
   *  and within the border (if present. )
   */
  std::string header() const noexcept { return fContent.header(); }
  TComponent &addHeader(std::string t = "") noexcept {
    fContent.addHeader(t);
    return *this;
  }

  /**
   * A Footer is a single line of text outside the padding of a component,
   *  and within the border (if present. )
   */
  std::string footer() const noexcept { return fContent.footer(); }
  TComponent &addFooter(std::string t = "") noexcept {
    fContent.addFooter(t);
    return *this;
  }

  /**
   * Adds a child component with the given generator.
   * Returns a reference to the created component.
   */
  TComponent &render(const std::string key, const Generator gen) noexcept {
    fSubComponents.emplace_back(TComponent(this, gen, key, fStyle));
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
  Border getBorder() const noexcept { return fStyle.getBorder(); }

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
  Margin getMargin() const noexcept { return fStyle.getMargin(); }

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
  Padding getPadding() const noexcept { return fStyle.getPadding(); }

  /**
   * Direction controls the way content and subComponents are stacked.
   */
  TStyle::Direction dir() const noexcept { return fStyle.direction(); }
  TComponent &horizontal() noexcept {
    fStyle.horizontal();
    return *this;
  }
  TComponent &vertical() noexcept {
    fStyle.vertical();
    return *this;
  }

  /**
   *
   */
  TComponent &collapse() noexcept {
    fStyle.collapse();
    return *this;
  }
  TComponent &expand() noexcept {
    fStyle.expand();
    return *this;
  }
  TComponent &toggle() noexcept {
    if (fStyle.getCollapsed()) {
      fStyle.expand();
    } else {
      fStyle.collapse();
    }
    return *this;
  }
  /*
   *
   */
  TComponent &onStandout() {
    fStyle.onStandout();
    return *this;
  }
  TComponent &offStandout() {
    fStyle.offStandout();
    return *this;
  }

  /*
   *
   */
  TComponent &onUnderline() {
    fStyle.onUnderline();
    return *this;
  }
  TComponent &offUnderline() {
    fStyle.offUnderline();
    return *this;
  }

  /*
   *
   */
  TComponent &onBlink() {
    fStyle.onBlink();
    return *this;
  }
  TComponent &offBlink() {
    fStyle.offBlink();
    return *this;
  }

  /*
   *
   */
  TComponent &onDim() {
    fStyle.onDim();
    return *this;
  }
  TComponent &offDim() {
    fStyle.offDim();
    return *this;
  }

  /*
   *
   */
  TComponent &onBold() {
    fStyle.onBold();
    return *this;
  }
  TComponent &offBold() {
    fStyle.offBold();
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

  bool focused() const noexcept { return focused(fKey); }

  TComponent &focus() noexcept {
    focus(fKey);
    return *this;
  }

  TComponent &unfocus() noexcept {
    unfocus(fKey);
    return *this;
  }

  TComponent &focusParent() noexcept {
    if (focused() && fParent != this) {
      fParent->focus();
      unfocus();
    }
    return *this;
  }

  TComponent &focusChildren() noexcept {
    if (focused() && fSubComponents.size() > 0) {
      fSubComponents.front().focus();
      unfocus();
    }
    return *this;
  }

  TComponent &focusPrevious() noexcept {
    if (focused() && fIndex - 1 >= 0) {
      fParent->fSubComponents[fIndex - 1].focus();
      unfocus();
    }
    return *this;
  }

  TComponent &focusNext() noexcept {
    if (focused() && fIndex + 1 < fParent->fSubComponents.size()) {
      fParent->fSubComponents[fIndex + 1].focus();
      unfocus();
    }
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
    if (direction == TStyle::Direction::HORIZONTAL) {
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
    w = std::max<int>(w, min.x());
    h = std::max<int>(h, min.y());

    if (fStyle.getCollapsed()) {
      if (dir() == TStyle::Direction::VERTICAL) {
        h = 1;
      } else {
        w = 1;
      }
    }

    return SizeD(w, h);
  }

  /**
   * Minimum size accounts for zero stretching.
   */
  SizeD minimumSize() const {
    SizeD subSize = {0, 0};
    for (auto &c : fSubComponents) {
      subSize += c.minimumSize();
    }
    SizeD c = fContent.size();
    int x, y;
    if (dir() == TStyle::Direction::HORIZONTAL) {
      x = subSize.x() + c.x();
      y = std::max<int>(subSize.y(), c.y());
    } else {
      x = std::max<int>(subSize.x(), c.x());
      y = subSize.y() + c.y();
    }
    return SizeD(x, y) + fStyle.size() - accountForDoubleCount();
  }

  /**
   * Size of container remaining to draw children.
   */
  SizeD inner() const { return size() - fStyle.size(); }

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
    if (dir() == TStyle::Direction::HORIZONTAL) {
      offX = fContent.sizeBody().x() + pad.x();
      offY = fContent.sizeHeader().y() + pad.y() - accountForDoubleCount().y();
    } else {
      offX = pad.x();
      offY = fContent.sizeBody().y() + pad.y();
    }
    if (fStyle.getCollapsed())
      offY = 1 + fStyle.sizeMargin().y();
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
  SubComponents fSubComponents = {};
  int fIndex = -1;

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

  std::string fKey = "INVALID_KEY";

  virtual bool focused(std::string uid) const {
    return fParent->focused(uid);
  }

  virtual void focus(std::string uid) {
    return fParent->focus(uid);
  }

  virtual void unfocus(std::string uid) {
    return fParent->unfocus(uid);
  }

  /**
   * When adding padding and content, subtract this vector to account
   * for border and title occupying the same line.
   */
  SizeD accountForDoubleCount() const {
    int y = fContent.sizeHeader().y() + fContent.sizeFooter().y();
    if (y > 0) {
      return SizeD{0, fStyle.hasBorder()};
    } else {
      return SizeD{0, 0};
    }
  }

  /**
   *
   */
  bool input(int key) {
    if (!focused()) {
      for (TComponent &c : fSubComponents) {
        if (c.input(key)) {
          return true;
        }
      }

      return false;
    } else {
      std::cout << key << std::endl;
      switch (key) {
      case 72:
        focusPrevious();
        break;
      case 74:
        focusChildren();
        break;
      case 75:
        focusParent();
        break;
      case 76:
        focusNext();
        break;
      }
      return true;
    };
  }

  /**
   * Recursively calculate the width that this component
   * and all children components will fill.
   * NOTE: This does not account for any wrapping.
   */
  int width() const {
    int w = fContent.sizeBody().x() + fStyle.size().x();
    for (auto &c : fSubComponents) {
      w += c.width();
    }
    int hw = fContent.sizeHeader().x() + fStyle.size().x();
    int fw = fContent.sizeFooter().x() + fStyle.size().x();
    return std::max<int>({hw, fw, w});
  }

  /**
   * Recursively calculate the height that this component
   * and all children components will fill.
   * NOTE: This does account for any wrapping.
   * NOTE: Because the title and footer is IN the border (if the border is
   * present) This has to be accounted for in order to not count the border
   * twice.
   */
  int height() const {
    int y = fContent.size().y() - accountForDoubleCount().y();
    int b = fStyle.size().y();
    // DOn't count the same line twice.
    int h = y + b;

    if (fStyle.getCollapsed())
      h = 1;

    for (auto &c : fSubComponents) {
      h += c.height();
    }

    return h;
  }
};
#endif
