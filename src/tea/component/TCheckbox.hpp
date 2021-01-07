#ifndef TCheckbox_DEFINED
#define TCheckbox_DEFINED

#include "TComponent.hpp"

typedef struct TCheckbox {
   TCheckbox(bool status, std::string line):fStatus(status), fLine(line){};

   void operator()(TComponent &c) {

      std::string line = "[";

      std::string val = fStatus ? "*" : " ";
      line.append(val);

      line.append("] ");
      line.append(fLine);

      c.addLine(line);
   }

   const bool fStatus = false;
   const std::string fLine = "";

} TCheckbox;

#endif
