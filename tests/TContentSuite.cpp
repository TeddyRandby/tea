#ifndef TContentSuite_DEFINED
#define TContentSuite_DEFINED

#include <gtest/gtest.h>
#include <iostream>
#include "../src/tea/component/TContent.hpp"

// The fixture for testing class Foo.
class TContentSuite: public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  TContentSuite():tea(TContent()) {
     // You can do set-up work for each test here.
  }

  ~TContentSuite() override {
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

   TContent tea;
};

TEST_F(TContentSuite, Initializes) {
   EXPECT_EQ(tea.header(), "");
   EXPECT_EQ(tea.body(), "");
   EXPECT_EQ(tea.footer(), "");
}

TEST_F(TContentSuite, ManagesBody) {
   tea.addLine("Hello\nWorld");
   tea.addLine("World");

   EXPECT_EQ(tea.body(), "Hello\nWorld\nWorld\n");

}

TEST_F(TContentSuite, ManagesHeader) {
   tea.addHeader("Hello World");
   tea.addHeader(" World");
   EXPECT_EQ(tea.header(), "Hello World World");

}

TEST_F(TContentSuite, ManagesFooter) {
   tea.addFooter("Hello World");
   tea.addFooter(" World");

   EXPECT_EQ(tea.footer(), "Hello World World");

}

TEST_F(TContentSuite, ManagesSize) {
   tea.addHeader("Hello World");
   tea.addHeader(" World");
   
   tea.addLine("Hello World");
   tea.addLine("Test \nWorld");

   tea.addFooter("Hi Universe");

   EXPECT_EQ(tea.sizeHeader().x(), 17);
   EXPECT_EQ(tea.sizeHeader().y(), 1);

   EXPECT_EQ(tea.sizeBody().x(), 11);
   EXPECT_EQ(tea.sizeBody().y(), 3);

   EXPECT_EQ(tea.sizeFooter().x(), 11);
   EXPECT_EQ(tea.sizeFooter().y(), 1);

   EXPECT_EQ(tea.size().x(), 17);
   EXPECT_EQ(tea.size().y(), 5);
}

TEST_F(TContentSuite, ManagesContentWrapping) {
   tea.addLine("Hello World");
   tea.addLine("Test \nWorld");

   EXPECT_EQ(tea.sizeBody(5).x(), 5);
   EXPECT_EQ(tea.sizeBody(5).y(), 7);

   EXPECT_EQ(tea.sizeBody(100).x(), 11);
   EXPECT_EQ(tea.sizeBody(100).y(), 3);

   EXPECT_EQ(tea.sizeBody(1).x(), 1);
   EXPECT_EQ(tea.sizeBody(1).y(), 24);
}

#endif
