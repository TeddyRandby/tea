#ifndef TComponentTests_DEFINED
#define TComponentTests_DEFINED

#include <gtest/gtest.h>
#include "../src/tea/screen/TApplication.hpp"

// The fixture for testing class Foo.
class TComponentSuite : public ::testing::Test {protected:
  // You can remove any or all of the following functions if their bodies would
  // // be empty.

  TComponentSuite() {
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
    tea = TApplication().setSize(400, 200);
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
    tea.generate();
    endwin();
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.

  TApplication tea;
};

TEST_F(TComponentSuite, Initializes) {
  tea.render("test", [](TComponent &test) {
    EXPECT_EQ(test.body(), "");
    test.addLine("Hello World");
    EXPECT_EQ(test.dir(), 0);
  });
}

TEST_F(TComponentSuite, GeneratesContent) {
  tea.render("test",[](auto &test) {
    // After generating, the line appears in the content.
    test.addLine("Hello World").addHeader("Title");
    EXPECT_EQ(test.body(), "Hello World\n");
    EXPECT_EQ(test.header(), "Title");
  });
}

TEST_F(TComponentSuite, ManagesSimpleContentSize) {
  tea.render("test",[](TComponent &test) {
    test.addLine("Hello World");
    test.addHeader("Title");

    auto sz = test.size();

    EXPECT_EQ(sz.x(), 398);
    EXPECT_EQ(sz.y(), 3);
  });
}

TEST_F(TComponentSuite, ManagesRelativeSize) {
  tea.render("test",[](TComponent &test) {
    test.addLine("Hello World").addHeader("Title").setWH(.5f, .3f);

    auto sz = test.size();
    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 199);
    EXPECT_EQ(sz.y(), 59);
  });
}

TEST_F(TComponentSuite, ManagesSimpleTitleSize) {
  tea.render("test",[](TComponent &test) {
    test.addLine("Hello World");
    test.addHeader("This title is longer than the content.");

    auto sz = test.size();
    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 398);
    EXPECT_EQ(sz.y(), 3);
  });
}

TEST_F(TComponentSuite, ManagesReverseSimpleTitleSize) {
  tea.render("test",[&](TComponent &test) {
    test.addLine("Hello World");
    test.addHeader("This title is longer than the content.");

    tea.horizontal();

    auto sz = test.size();

    EXPECT_EQ(sz.x(), 40);
    EXPECT_EQ(sz.y(), 198);
  });}

TEST_F(TComponentSuite, ManagesReverseSimpleContentSize) {
  tea.render("test",[&](TComponent &test) {
    test.addLine("Hello World").addHeader("Title");

    tea.horizontal();

    auto sz = test.size();
    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 13);
    EXPECT_EQ(sz.y(), 198);
  });
}

TEST_F(TComponentSuite, ManagesMarginContentSize) {
  tea.render("test",[](TComponent &test) {
    test.addLine("Hello World").addHeader("Title").setMargin(2);

    auto sz = test.size();
    EXPECT_EQ(sz.x(), 398);
    EXPECT_EQ(sz.y(), 7);
  });
}

TEST_F(TComponentSuite, ManagesReverseMarginContentSize) {
  tea.render("test",[&](TComponent &test) {
    test.addLine("Hello World").addHeader("Title").setMargin(2);

    tea.horizontal();

    auto sz = test.size();
    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 17);
    EXPECT_EQ(sz.y(), 198);
  });
}

TEST_F(TComponentSuite, ManagesBorderSize) {
  tea.render("test",[&](TComponent &test) {
    test.addLine("Hello World").addHeader("Title").setBorder(0);
    tea.setBorder(0);

    auto sz = test.size();
    EXPECT_EQ(sz.x(), 400);
    EXPECT_EQ(sz.y(), 2);

    tea.setBorder({1, 1, 2, 2});
    tea.vertical();

    sz = test.size();
    EXPECT_EQ(sz.x(), 396);
    EXPECT_EQ(sz.y(), 2);
  });
}

TEST_F(TComponentSuite, ManagesReverseBorderSize) {
  tea.render("test",[&](TComponent &test) {
    test.addLine("Hello World").addHeader("Title").setBorder(0);

    tea.horizontal();
    tea.setBorder(0);

    auto sz = test.size();
    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 11);
    EXPECT_EQ(sz.y(), 200);

    tea.setBorder({2, 2, 1, 1});
    tea.horizontal();

    sz = test.size();
    EXPECT_EQ(sz.x(), 11);
    EXPECT_EQ(sz.y(), 196);
  });
}

TEST_F(TComponentSuite, ManagesTitleAndBorderSize) {
  tea.render("test",[&](TComponent &test) {
    test.addLine("Hello World").addHeader("Title").setBorder(0);

    auto sz = test.size();

    // After generation, new size includes content line.
    EXPECT_EQ(sz.x(), 398);
    EXPECT_EQ(sz.y(), 2);
  });
}

TEST_F(TComponentSuite, ManagesMinimumSize) {
  tea.render("test",[&](TComponent &test) {
    test.addLine("Hello World").addHeader("Title");

    auto sz = test.minimumSize();

    EXPECT_EQ(sz.x(), 13);
    EXPECT_EQ(sz.y(), 3);

    test.setBorder({2, 2, 1, 1});

    sz = test.minimumSize();
    EXPECT_EQ(sz.x(), 13);
    EXPECT_EQ(sz.y(), 5);

    test.setBorder({1, 1, 2, 2});

    sz = test.minimumSize();
    EXPECT_EQ(sz.x(), 15);
    EXPECT_EQ(sz.y(), 3);

    test.render("child",[&](TComponent &child) {
      child.setBorder(2);
      auto csz = child.minimumSize();
      EXPECT_EQ(csz.x(), 4);
      EXPECT_EQ(csz.y(), 4);

      sz = test.minimumSize();
      EXPECT_EQ(sz.x(), 15);
      EXPECT_EQ(sz.y(), 7);
    });
  });
}

TEST_F(TComponentSuite, ManagesChildrenOffset) {
  tea.render("test",[&](TComponent &test) {
    test.addLine("Hello World").addHeader("Title");

    auto sz = test.offset();

    EXPECT_EQ(sz.x(), 1);
    EXPECT_EQ(sz.y(), 2);

    test.setBorder({2, 2, 1, 1});
    sz = test.offset();

    EXPECT_EQ(sz.x(), 1);
    EXPECT_EQ(sz.y(), 3);

    test.setBorder({1, 1, 2, 2});
    sz = test.offset();

    EXPECT_EQ(sz.x(), 2);
    EXPECT_EQ(sz.y(), 2);
  });
}

TEST_F(TComponentSuite, ManagesNestedChildrenSimpleSize) {
  tea.render("test",[](TComponent &test) {
    test.addLine("Hello World")
        .addHeader("Title")
        .render("child",[&](TComponent &child) {
          child.addHeader("Child Title");
          child.addLine("Child Line");

          child.setBorder({2, 2, 1, 1});

          auto sz = test.size();

          EXPECT_EQ(sz.x(), 398);
          EXPECT_EQ(sz.y(), 8);
        });
  });
}

TEST_F(TComponentSuite, ManagesReverseNestedChildrenSimpleSize) {
  tea.horizontal();
  tea.render("test",[](TComponent &test) {
    test.addLine("Hello World")
        .addHeader("Title")
        .render("child",[&](TComponent &child) {
          child.addHeader("Child Title");
          child.addLine("Child Line");

          child.setBorder({1, 1, 2, 2});

          auto sz = test.size();

          EXPECT_EQ(sz.x(), 28);
          EXPECT_EQ(sz.y(), 198);
        });
  });
}

TEST_F(TComponentSuite, ManagesSiblingChildrenSimpleSize) {
  tea.render("test",[](TComponent &test) {
    test.addLine("Hello World")
        .addHeader("Title")
        .render("child",[](TComponent &child) {
          child.addHeader("Child Title");
          child.addLine("Child Line");
        })
        .render("sibling",[&](TComponent &sibling) {
          sibling.addHeader("Sibling Title");
          sibling.addLine("Sibling Line");

          auto sz = test.size();
          // The siblings should be generated as well.
          EXPECT_EQ(sz.x(), 398);
          EXPECT_EQ(sz.y(), 9);
        });
  });
}

TEST_F(TComponentSuite, InheritsStylesFromParent) {
  tea.render("test",[](TComponent &test) {
    test.setPadding(3);
    test.setBorder(0);
    test.render("child",[](TComponent &child) {
      EXPECT_EQ(child.getPadding(), Padding(3, 3, 3, 3));
      EXPECT_EQ(child.getBorder(), Border(0, 0, 0, 0));
    });
  });
}

TEST_F(TComponentSuite, ManagesCollapsing) {
  tea.render("test",[](TComponent &test) {
    test.setPadding(3);
    test.collapse();

    auto sz = test.size();
    EXPECT_EQ(sz.x(), 398);
    EXPECT_EQ(sz.y(), 1);
  });
}

TEST_F(TComponentSuite, ManagesFocus) {
  EXPECT_TRUE(tea.TComponent::focused());

  TComponent *first;
  tea.render("test",[&](TComponent &test) {
    tea.focusChildren();
    EXPECT_TRUE(!tea.TComponent::focused());
    EXPECT_TRUE(test.focused());

    test.focusParent();
    EXPECT_TRUE(tea.TComponent::focused());
    EXPECT_TRUE(!test.focused());

    first = &test;
  });

  tea.render("testSib",[&](TComponent &testSib) {
    tea.focusChildren();
    EXPECT_TRUE(!tea.TComponent::focused());
    EXPECT_TRUE(!testSib.focused());

    testSib.focusParent();
    EXPECT_TRUE(!tea.TComponent::focused());
    EXPECT_TRUE(!testSib.focused());

    EXPECT_TRUE(first->focused());

    first->focusNext();
    EXPECT_TRUE(!tea.TComponent::focused());
    EXPECT_TRUE(testSib.focused());
    EXPECT_TRUE(!first->focused());

    testSib.focusPrevious();
    EXPECT_TRUE(!tea.TComponent::focused());
    EXPECT_TRUE(!testSib.focused());
    EXPECT_TRUE(first->focused());
  });
};

#endif
