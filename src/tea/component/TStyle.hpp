#ifndef TSyle_DEFINED
#define TSyle_DEFINED

#include "../utils/TVec.hpp"

class TStyle {

public:
    TStyle() {};
    ~TStyle() {};

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
    /**
     * A Border is drawn outlining the component.
     */
    Border fBorder = Border(1,1,1,1);

    /**
     * Padding is the space between a component's content and its border.  
     */
    Padding fPadding = Padding(0,0,0,0);

    /**
     * Margin is the space between components.
     */
    Margin fMargin = Margin(0,0,0,0);

};

#endif

