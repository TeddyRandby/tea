#ifndef TTestNode_DEFINED
#define TTestNode_DEFINED

#include "TComponent.hpp"

class TTestNode : public TNode {

    public:
    TTestNode(): TNode(this, [](auto&){}) {}

    /**
     * A dummy node for testing. Acts as a "base-case", where the
     * top level node would.
     */
    SizeD size() const override {
        return {400,200};
    }
    
};

#endif
