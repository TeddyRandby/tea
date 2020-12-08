#ifndef TContent_DEFINED
#define TContent_DEFINED

#include "TVec2.hpp"
#include <string>
#include <vector>

class TContent {

public:

  typedef std::string Lines;
  typedef std::string Titles;

  TContent() {}
  ~TContent() {}

  /**
   * Lines added automatically have '/n' attached.
   * These will be drawn within the box.
   */
  TContent& addLine(const std::string l) {
    (fLines += l) += '\n';
    return *this;
  }

  /**
   * Lines added automatically have ' ' attached.
   * These will be drawn on the top-border of the box.
   */
  TContent& addTitle(const std::string t) {
   (fTitles += t) += ' ';
   return *this;
  }

  /**
   * Reset the data.
   */
   TContent& flush() {
    fLines = "";
    fTitles = "";
    return *this;
   }

  /**
   * Return the raw string content.
   * NOTE: The string is copied, for now.
   */
  Lines content() const {
    return fLines;
  }

  /**
   * Return the raw string content.
   * NOTE: The string is copied, for now.
   */
  Titles title() const {
    return fTitles;
  }

  /**
   * Calculate the size of the fContent string
   */
  SizeD sizeContent(const int w=-11) const {
    return sizeString(fLines, w);
  }

  /**
   * Calculate the size of the fContent string
   */
  SizeD sizeTitle(const int w=-1) const {
    return sizeString(fTitles, w);
  }

private:
  Titles fTitles = "";
  Lines fLines = "";

  /**
   * Calculate the size of the fContent string
   * NOTE: Separates the string into lines.
   *    returns {longest line, num lines}
   * NOTE: If no sep chars are present, returns {length,0}
   * NOTE: Line length exclues the \n char.
   * NOTE: Giving a maxw turns ON wrapping.
   */
  SizeD sizeString(const std::string &str, const int maxw=-1) const {
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
  }

};

#endif
