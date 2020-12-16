#ifndef TContent_DEFINED
#define TContent_DEFINED

#include "../utils/TVec.hpp"
#include <string>

class TContent {

public:
  TContent() {}
  ~TContent() {}

  /**
   * Lines added automatically have '/n' attached.
   * These will be drawn within the box.
   */
  TContent &addLine(const std::string &l) {
    (fBody += l) += '\n';
    return *this;
  }

  /**
   * Lines added automatically have ' ' attached.
   * These will be drawn on the top-border of the box.
   */
  TContent &addHeader(const std::string &h) {
    (fHeader += h) + ' ';
    return *this;
  }

  TContent &addFooter(const std::string &f) {
    (fFooter += f) + ' ';
    return *this;
  }

  /**
   * Return the raw string content.
   * NOTE: The string is copied, for now.
   */
  std::string header() const { return fHeader; }

  std::string body() const { return fBody; }

  std::string footer() const { return fFooter; }

  /**
   * Calculate the size of the a string field.
   * Size (widest line, num lines)
   */
  SizeD sizeHeader(const int w = -1) const { return sizeString(fHeader, w); }

  SizeD sizeBody(const int w = -1) const { return sizeString(fBody, w); }

  SizeD sizeFooter(const int w = -1) const { return sizeString(fFooter, w); }

  SizeD size(const int w = -1) const {
    const SizeD h = sizeHeader(w);
    const SizeD b = sizeBody(w);
    const SizeD f = sizeFooter(w);

    int x,y;
    x = std::max<int>({h.x(), b.x(), f.x()});
    y = h.y() + b.y() + f.y();
    return SizeD{x,y};
  }

private:
  std::string fHeader = "";
  std::string fBody = "";
  std::string fFooter = "";

  /**
   * Calculate the size of the fContent string
   * NOTE: Separates the string into lines.
   *    returns {longest line, num lines}
   * NOTE: If no sep chars are present, returns {length,0}
   * NOTE: Line length exclues the \n char.
   * NOTE: Giving a maxw turns ON wrapping.
   */
  SizeD sizeString(const std::string &str, const int maxw = -1) const {
    int longest = -1;
    int length = 0;
    int count = 0;

    for (char c : str) {

      if (c == '\n') {
        longest = std::max<int>(length, longest);
        length = 0;
        count++;
      } else {
        length++;
      }

      // Wrap if the line is maxed out.
      if (maxw != -1 && length == maxw) {
        longest = std::max<int>(length, longest);
        length = 0;
        count++;
      }
    }

    if (longest == -1)
      longest = length;
    if (count == 0 && str.size() > 0)
      count++;

    return SizeD(longest, count);
  }};

#endif
