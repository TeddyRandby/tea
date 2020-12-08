#ifndef TComponentTests_DEFINED
#define TComponentTests_DEFINED

#include <gtest/gtest.h>
#include "../src/TApplication.hpp"
#include "../src/TComponent.hpp"
#include <iostream>

// The fixture for testing class Foo.
class TComponentSuite : public ::testing::Test {protected:
  // You can remove any or all of the following functions if their bodies would
  // // be empty.

  TComponentSuite() : tea([](TComponent &tea) {}, true) {
    // You can do set-up work for each test here.
  }

  ~TComponentSuite() override {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
    // Code here will be called immediately after the constructor (right
    // before each test).
    tea = TApplication([](auto &tea) {}, true);
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
  tea.generate();
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.

  TApplication tea;};

TEST_F(TComponentSuite, Initializes) {
  tea.addComponent([](TComponent &test) {
    EXPECT_EQ(test.content(), "");
    test.addLine("Hello World");
    auto pos = test.absPos();
    EXPECT_EQ(pos.x(), 0);
    EXPECT_EQ(pos.y(), 0);
    EXPECT_EQ(test.dir(), 0);
  });
}

TEST_F(TComponentSuite, GeneratesContent) {
  tea.addComponent([](auto &test) {
    // After generating, the line appears in the content.
    test.addLine("Hello World").addTitle("Title");
    EXPECT_EQ(test.content(), "Hello World\n");
    EXPECT_EQ(test.title(), "Title ");
  });
}

TEST_F(TComponentSuite, ManagesSimpleContentSize) {
  tea.addComponent([](TComponent &test) {
    test.addLine("Hello World");
    test.addTitle("Title");

    auto sz = test.size();

    EXPECT_EQ(sz.x(), 398);
    EXPECT_EQ(sz.y(), 3);
  });
}

TEST_F(TComponentSuite, ManagesRelativeSize) {
  tea.addComponent([](TComponent &test) {
    test.addLine("Hello World").addTitle("Title").setWH(.5, .3);

    auto sz = test.size();
    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 199);
    EXPECT_EQ(sz.y(), 59);
  });
}

TEST_F(TComponentSuite, ManagesSimpleTitleSize) {
  tea.addComponent([](TComponent &test) {
    test.addLine("Hello World");
    test.addTitle("This title is longer than the content.");

    auto sz = test.size();
    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 398);
    EXPECT_EQ(sz.y(), 3);
  });
}

TEST_F(TComponentSuite, ManagesReverseSimpleTitleSize) {
  tea.addComponent([&](TComponent &test) {
    test.addLine("Hello World");
    test.addTitle("This title is longer than the content.");

    tea.toggleDirection();

    auto sz = test.size();
    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 39);
    EXPECT_EQ(sz.y(), 198);
  });}

TEST_F(TComponentSuite, ManagesReverseSimpleContentSize) {
  tea.addComponent([&](TComponent &test) {
    test.addLine("Hello World").addTitle("Title");

    tea.toggleDirection();

    auto sz = test.size();
    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 13);
    EXPECT_EQ(sz.y(), 198);
  });
}

TEST_F(TComponentSuite, ManagesMarginContentSize) {
  tea.addComponent([](TComponent &test) {
    test.addLine("Hello World").addTitle("Title").setMargin(2);

    auto sz = test.size();
    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 398);
    EXPECT_EQ(sz.y(), 5);
  });
}

TEST_F(TComponentSuite, ManagesReverseMarginContentSize) {
  tea.addComponent([&](TComponent &test) {
    test.addLine("Hello World").addTitle("Title").setMargin(2);

    tea.toggleDirection();

    auto sz = test.size();
    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 15);
    EXPECT_EQ(sz.y(), 198);
  });
}

TEST_F(TComponentSuite, ManagesBorderSize) {
  tea.addComponent([&](TComponent &test) {
    test.addLine("Hello World").addTitle("Title").toggleBorder();

    tea.toggleBorder();

    auto sz = test.size();
    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 400);
    EXPECT_EQ(sz.y(), 2);
  });
}

TEST_F(TComponentSuite, ManagesReverseBorderSize) {
  tea.addComponent([&](TComponent &test) {
    test.addLine("Hello World").addTitle("Title").toggleBorder();

    tea.toggleDirection();
    tea.toggleBorder();

    auto sz = test.size();
    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 11);
    EXPECT_EQ(sz.y(), 200);
  });
}

TEST_F(TComponentSuite, ManagesTitleAndBorderSize) {
  tea.addComponent([&](TComponent &test) {
    test.addLine("Hello World").addTitle("Title").toggleBorder();

    auto sz= test.size();

    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 398);
    EXPECT_EQ(sz.y(), 2);

  });
}

TEST_F(TComponentSuite, ManagesNestedChildrenSimpleSize) {
  tea.addComponent([](TComponent &test) {
    test.addLine("Hello World")
        .addTitle("Title")
        .addComponent([&](TComponent &child) {
          child.addTitle("Child Title");
          child.addLine("Child Line");
          auto sz = test.size();
          // The child should be generated as well.
          EXPECT_EQ(sz.x(), 398);
          EXPECT_EQ(sz.y(), 6);
        });
  });
}

TEST_F(TComponentSuite, ManagesSiblingChildrenSimpleSize) {
  tea.addComponent([](TComponent &test) {
    test.addLine("Hello World")
        .addTitle("Title")
        .addComponent([](TComponent &child) {
          child.addTitle("Child Title");
          child.addLine("Child Line");
        })
        .addComponent([&](TComponent &sibling) {
          sibling.addTitle("Sibling Title");
          sibling.addLine("Sibling Line");

          auto sz = test.size();
          // The siblings should be generated as well.
          EXPECT_EQ(sz.x(), 398);
          EXPECT_EQ(sz.y(), 9);
        });
  });
}

#endif
