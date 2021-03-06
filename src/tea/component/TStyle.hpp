#ifndef TSyle_DEFINED
#define TSyle_DEFINED

#include "ncurses.h"
#include "../utils/TVec.hpp"

class TStyle {

public:
    enum Direction { VERTICAL, HORIZONTAL };
    TStyle() {};
    ~TStyle() {};

    /*
     *
     */
    TStyle &onStandout() {
       fAttributes = fAttributes | A_STANDOUT;
       return *this;
    }
    TStyle &offStandout() {
       fAttributes = fAttributes & ~A_STANDOUT;
       return *this;
    }

    /*
     *
     */
    TStyle &onUnderline() {
       fAttributes = fAttributes | A_UNDERLINE;
       return *this;
    }
    TStyle &offUnderline() {
       fAttributes = fAttributes & ~A_UNDERLINE;
       return *this;
    }

    /*
     *
     */
    TStyle &onBlink() {
       fAttributes = fAttributes | A_BLINK;
       return *this;
    }
    TStyle &offBlink() {
       fAttributes = fAttributes & ~A_BLINK;
       return *this;
    }

    /*
     *
     */
    TStyle &onDim() {
       fAttributes = fAttributes | A_DIM;
       return *this;
    }
    TStyle &offDim() {
       fAttributes = fAttributes & ~A_DIM;
       return *this;
    }

    /*
     *
     */
    TStyle &onBold() {
       fAttributes = fAttributes | A_BOLD;
       return *this;
    }
    TStyle &offBold() {
       fAttributes = fAttributes & ~A_BOLD;
       return *this;
    }

    /*
     *
     */
    TStyle &collapse() {
        fCollapsed = true; 
        return *this;
    }
    TStyle &expand() {
        fCollapsed = false; 
        return *this;
    }
    bool getCollapsed() const {
        return fCollapsed;
    }

    /*
     *
     */
    TStyle& horizontal() {
        fDirection = Direction::HORIZONTAL;        
        return *this;
    }

    TStyle& vertical() {
        fDirection = Direction::VERTICAL;        
        return *this;
    }

    Direction direction() const {
        return fDirection;
    }

    /*
     *
     */
    TStyle& setBorder(const Border &b) {
        fBorder = b;        
        return *this;
    }
    TStyle& setBorder(const int b) {
        return setBorder({b,b,b,b});
    }
    bool hasBorder() const {
        return fBorder != Border({0,0,0,0});
    }
    Border getBorder() const {
        return fBorder;
    }
    SizeD sizeBorder() const {
        return SizeD(fBorder.l() + fBorder.r(), fBorder.t() + fBorder.b());
    }

    /*
     *
     */
    TStyle& setPadding(const Padding &p) {
        fPadding = p;        
        return *this;
    }
    TStyle& setPadding(const int p) {
        return setPadding({p,p,p,p});
    }
    bool hasPadding() const {
        return fPadding == Padding({0,0,0,0});
    }
    Padding getPadding() const {
        return fPadding;
    }
    SizeD sizePadding() const {
        return SizeD(fPadding.l() + fPadding.r(), fPadding.t() + fPadding.b());
    }

    /*
     *
     */
    TStyle& setMargin(const Margin &m) {
        fMargin = m; 
        return *this;
    }
    TStyle& setMargin(const int m) {
        return setMargin({m,m,m,m});
    }
    bool hasMargin() const {
        return fMargin == Margin({0,0,0,0});
    }
    Margin getMargin() const {
        return fMargin;
    }
    SizeD sizeMargin() const {
        return SizeD(fMargin.l() + fMargin.r(), fMargin.t() + fMargin.b());
    }

    chtype attributes() const noexcept {
        return fAttributes;
    }

    /**
     * Return the total MPB in the x and y direction.
     */
    SizeD size() const noexcept {
        auto pad = fBorder + fMargin + fPadding;
        return SizeD(pad.l() + pad.r(), pad.t() + pad.b()); 
    }

    /**
     * Return the (sum left MPB, sum top MPB)
     */
    SizeD offset() const noexcept {
        auto pad = fBorder + fMargin + fPadding;
        return SizeD(pad.l(), pad.t());
    }

private:
    // TVec4 {top, bottom, left, right}
    /**
     * A Border is drawn outlining the component.
     */
    Border fBorder = Border{1,1,1,1};

    /**
     * Padding is the space between a component's content and its border.  
     */
    Padding fPadding = Padding{0,0,0,0};

    /**
     * Margin is the space between components.
     */
    Margin fMargin = Margin{0,0,0,0};

    /**
     *
     */
    Direction fDirection = Direction::VERTICAL;

    /**
     *
     */
    bool fCollapsed = false;

    /**
     *
     */
    chtype fAttributes = 0;
};
#endif
