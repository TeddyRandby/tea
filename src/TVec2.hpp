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

  TVec2 operator=(const TVec2 &v) { return {fX, fY}; }

  TVec2 operator-(TVec2<T> delta) const { return {fX - delta.x(), fY - delta.y()}; }
  TVec2 operator-=(TVec2<T> delta) { 
    fX -= delta.x();
    fY -= delta.y();
    return *this;
  };

  TVec2 operator+(TVec2<T> delta) const { return {fX + delta.x(), fY + delta.y()}; }
  TVec2 operator+=(TVec2<T> delta) { 
    fX += delta.x();
    fY += delta.y();
    return *this;
  };

  bool operator==(TVec2<T> o) const { return fX == o.x() && fY == o.y(); }

  constexpr T x() const { return fX; }
  constexpr T y() const { return fY; }

private:
  T fX;
  T fY;
};

typedef TVec2<int> SizeD;
typedef TVec2<float> SizeN;
typedef TVec2<int> Offset;

#endif
