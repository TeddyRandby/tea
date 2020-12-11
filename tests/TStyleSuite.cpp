#ifndef TStyleSuite_DEFINED
#define TStyleSuite_DEFINED

#include <gtest/gtest.h>
#include "../src/tea/component/TStyle.hpp"

// The fixture for testing class Foo.
class TStyleSuite: public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TStyleSuite() {
     // You can do set-up work for each test here.
  }

  ~TStyleSuite() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
     tea = TStyle();
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
  TStyle tea;
};

TEST_F(TStyleSuite, Initializes) {
   EXPECT_EQ(tea.size(), SizeD(2,2));
}

TEST_F(TStyleSuite, Sets) {
   tea.setBorder(0);
   EXPECT_EQ(tea.size(), SizeD(0,0));

   tea.setPadding({2,2,1,1});
   EXPECT_EQ(tea.size(), SizeD(2,4));

   tea.setMargin({1,1,2,2});
   EXPECT_EQ(tea.size(), SizeD(6,6));
}

#endif
