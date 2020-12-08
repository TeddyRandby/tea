#ifndef TSubComponents_DEFINED
#define TSubComponents_DEFINED 

#include <vector>

class TSubComponents{
    
public: 
  enum Direction { VERTICAL, HORIZONTAL };
protected:
  typedef std::vector<TComponent> ChildrenType;

public:
  TSubComponents(){};  
  ~TSubComponents(){};  

  Direction dir() const noexcept { return fDir; }
  void toggleDirection() noexcept {
    if (fDir == Direction::HORIZONTAL) {
        fDir = Direction::VERTICAL;
    } else {
        fDir = Direction::HORIZONTAL;
    }
  }

   TComponent &addSubComponent(TComponent &c) {
    return fSubComponents.emplace_back(c);  
   }

  /**
   * NOTE: Needs to account for chilren direction.
   * 
   * Default values of -1 turn of wrapping in that direction.
   */
  SizeD size(const int w=-1, const int h=-1) const {
    SizeD d = {0,0};
    return d;
  }

private:
  ChildrenType fSubComponents= {};
  Direction fDir = Direction::VERTICAL;

};

#endif
