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
   EXPECT_EQ(tea.content(), "");
   EXPECT_EQ(tea.title(), "");
}

TEST_F(TContentSuite, ManagesLines) {
   tea.addLine("Hello\nWorld");
   tea.addLine("World");

   EXPECT_EQ(tea.content(), "Hello\nWorld\nWorld\n");

   tea.flush();

   EXPECT_EQ(tea.content(), "");
}

TEST_F(TContentSuite, ManagesTitles) {
   tea.addTitle("Hello World");
   tea.addTitle(" World");

   EXPECT_EQ(tea.title(), "Hello World  World ");

   tea.flush();

   EXPECT_EQ(tea.title(), "");
}

TEST_F(TContentSuite, ManagesSize) {
   tea.addTitle("Hello World");
   tea.addTitle(" World");
   
   tea.addLine("Hello World");
   tea.addLine("Test \nWorld");

   EXPECT_EQ(tea.sizeTitle().x(), 19);
   EXPECT_EQ(tea.sizeTitle().y(), 1);

   EXPECT_EQ(tea.sizeContent().x(), 11);
   EXPECT_EQ(tea.sizeContent().y(), 3);

   tea.flush();

   EXPECT_EQ(tea.sizeTitle().x(), 0);
   EXPECT_EQ(tea.sizeTitle().y(), 0);
   EXPECT_EQ(tea.sizeContent().x(), 0);
   EXPECT_EQ(tea.sizeContent().y(), 0);
}

TEST_F(TContentSuite, ManagesContentWrapping) {
   tea.addLine("Hello World");
   tea.addLine("Test \nWorld");

   EXPECT_EQ(tea.sizeContent(5).x(), 5);
   EXPECT_EQ(tea.sizeContent(5).y(), 7);

   EXPECT_EQ(tea.sizeContent(100).x(), 11);
   EXPECT_EQ(tea.sizeContent(100).y(), 3);

   EXPECT_EQ(tea.sizeContent(1).x(), 1);
   EXPECT_EQ(tea.sizeContent(1).y(), 24);

   tea.flush();

   EXPECT_EQ(tea.sizeContent().x(), 0);
   EXPECT_EQ(tea.sizeContent().y(), 0);
}

#endif
