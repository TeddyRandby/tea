#ifndef TVec2_DEFINED
#define TVec2_DEFINED

#include <type_traits>

template <typename T> concept Numerical = std::is_arithmetic<T>::value;

template <Numerical T> class TVec2 {
public:

  TVec2(const TVec2 &v) : fX(v.x()), fY(v.y()){};
  TVec2(T x, T y) : fX(x), fY(y){};

  TVec2 operator-(T delta) const { return {fX - delta, fY - delta}; }

  TVec2 operator+(T delta) const { return {fX + delta, fY + delta}; }

  TVec2 operator*(T delta) const { return {fX * delta, fY * delta}; }

  TVec2& operator=(const TVec2<T> &v) {
    this->fX = v.x();
    this->fY = v.y();
    return *this;
  }

  TVec2 operator-(TVec2<T> delta) const { return {fX - delta.x(), fY - delta.y()}; }
  TVec2 operator-=(TVec2<T> delta) { 
    fX -= delta.x();
    fY -= delta.y();
    return *this;
  }

  TVec2 operator+(TVec2<T> delta) const { return {fX + delta.x(), fY + delta.y()}; }
  TVec2 operator+=(TVec2<T> delta) { 
    fX += delta.x();
    fY += delta.y();
    return *this;
  };

  TVec2 operator*(TVec2<T> delta) const { return {fX * delta.x(), fY * delta.y()}; }
  TVec2 operator*=(TVec2<T> delta) { 
    fX *= delta.x();
    fY *= delta.y();
    return *this;
  };

  bool operator==(TVec2<T> o) const { return fX == o.x() && fY == o.y(); }
  bool operator!=(TVec2<T> o) const { return fX != o.x() || fY != o.y(); }

  T x() const { return fX; }
  T y() const { return fY; }

private:
  T fX;
  T fY;
};

template <Numerical T> class TVec4 {
public:

  TVec4(const TVec4 &v) : fT(v.t()), fB(v.b()),fL(v.l()), fR(v.r()){};
  TVec4(T t, T b, T l, T r) : fT(t), fB(b), fL(l), fR(r){};

  TVec4 operator-(T delta) const { return {fT - delta, fB - delta, fL - delta, fR - delta}; }

  TVec4 operator+(T delta) const { return {fT + delta, fB + delta, fL + delta, fR + delta}; }

  TVec4& operator=(const TVec4<T> &v) {
    this->fT = v.t();
    this->fB = v.b();
    this->fL = v.l();
    this->fR = v.r();
    return *this;
  }

  TVec4 operator-(TVec4<T> delta) const { return {fT - delta.t(), fB - delta.b(), fL - delta.l(), fR - delta.r()}; }
  TVec4 operator-=(TVec4<T> delta) { 
    fT -= delta.t();
    fB -= delta.b();
    fL -= delta.l();
    fR -= delta.r();
    return *this;
  };

  TVec4 operator+(TVec4<T> delta) const { return {fT + delta.t(), fB + delta.b(), fL + delta.l(), fR + delta.r()}; }
  TVec4 operator+=(TVec4<T> delta) { 
    fT += delta.t();
    fB += delta.b();
    fL += delta.l();
    fR += delta.r();
    return *this;
  };

  bool operator==(TVec4<T> o) const { 
    return fT == o.t() && 
           fB == o.b() &&
           fL == o.l() &&
           fR == o.r();
  }

  bool operator!=(TVec4<T> o) const { 
    return fT != o.t() || 
           fB != o.b() ||
           fL != o.l() ||
           fR != o.r();
  }

  T t() const { return fT; }
  T b() const { return fB; }
  T l() const { return fL; }
  T r() const { return fR; }

private:
  T fT;
  T fB;
  T fL;
  T fR;
};

typedef TVec2<int> SizeD;
typedef TVec2<float> SizeN;
typedef TVec2<int> Offset;

typedef TVec4<int> Margin;
typedef TVec4<int> Padding;
typedef TVec4<int> Border;

#endif
