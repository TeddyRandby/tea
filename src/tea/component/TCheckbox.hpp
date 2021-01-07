#ifndef TCheckbox_DEFINED
#define TCheckbox_DEFINED

#include "TComponent.hpp"

typedef struct TCheckbox {
   TCheckbox(bool status, std::string line, std::function<bool(int)> inputHandler=[](int key){return true;}):fStatus(status), fLine(line), fInputHandler(inputHandler){};

   void operator()(TComponent &c) {
      c.setBorder(0);

      c.onInput(fInputHandler);

      std::string line = "[";

      std::string val = fStatus ? "*" : " ";
      line.append(val);

      line.append("] ");
      line.append(fLine);

      c.addLine(line);
   }

   const bool fStatus = false;
   const std::string fLine = "";
   const std::function<bool(int)> fInputHandler;
} TCheckbox;

#endif
