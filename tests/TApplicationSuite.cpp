#ifndef TApplicationSuite_DEFINED 
#define TApplicationSuite_DEFINED 

#include <gtest/gtest.h>
#include "../src/tea/screen/TApplication.hpp"

// The fixture for testing class Foo.
class TApplicationSuite: public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TApplicationSuite() {
     // You can do set-up work for each test here.
  }

  ~TApplicationSuite() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
     tea = TApplication();
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
     tea.generate();
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
  TApplication tea;
};

TEST_F(TApplicationSuite, InitializesTestMode) {
   EXPECT_TRUE(tea.size().x() != 0); 
   EXPECT_TRUE(tea.size().y() != 0);
}


#endif
