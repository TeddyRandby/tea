#ifndef TVec2Suite_DEFINED
#define TVec2Suite_DEFINED

#include <gtest/gtest.h>
#include "../src/tea/utils/TVec2.hpp"
#include <cmath>

// The fixture for testing class Foo.
class TVec2Suite: public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TVec2Suite(): vi(10,15), vf(.4f,.5f) {
     // You can do set-up work for each test here.
  }

  ~TVec2Suite() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
  const TVec2<int> vi;
  const TVec2<float> vf;
};

bool floatEquals(const float f1,const float f2) {
   return std::abs(f1 - f2) < 0.001f; 
};

TEST_F(TVec2Suite, Initializes) {
   EXPECT_EQ(vi.x(), 10);
   EXPECT_EQ(vi.y(), 15);

   EXPECT_TRUE(floatEquals(vf.x(), .4f));
   EXPECT_TRUE(floatEquals(vf.y(), .5f));
}

TEST_F(TVec2Suite, Adds) {
   const TVec2 i = vi + 2;
   
   EXPECT_EQ(i.x(), 12);
   EXPECT_EQ(i.y(), 17);

   const TVec2 f = vf + 2.0;

   EXPECT_TRUE(floatEquals(f.x(), 2.4f));
   EXPECT_TRUE(floatEquals(f.y(), 2.5f));

   const TVec2 i2 = vi + i;

   EXPECT_EQ(i2.x(), 22);
   EXPECT_EQ(i2.y(), 32);

   const TVec2 f2 = vf + f;
   EXPECT_TRUE(floatEquals(f2.x(), 2.8f));
   EXPECT_TRUE(floatEquals(f2.y(), 3.0f));
   
}

TEST_F(TVec2Suite, Subtracts) {
   const auto i = vi - 2;
   
   EXPECT_EQ(i.x(), 8);
   EXPECT_EQ(i.y(), 13);

   const auto f = vf - 2.0;

   EXPECT_TRUE(floatEquals(f.x(), -1.6f));
   EXPECT_TRUE(floatEquals(f.y(), -1.5f));
   
   const TVec2 i2 = vi - i;

   EXPECT_EQ(i2.x(), 2);
   EXPECT_EQ(i2.y(), 2);

   const TVec2 f2 = vf - f;
   EXPECT_TRUE(floatEquals(i2.x(), 2.f));
   EXPECT_TRUE(floatEquals(i2.y(), 2.f));
}

#endif
