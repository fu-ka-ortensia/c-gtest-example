#include <gtest/gtest.h>

extern "C" {
    #include "module_template.h"
}

class ModuleTemplateTest : public ::testing::Test {
protected:
    void SetUp() override {
        /* Initialize any resources needed for tests */
    }

    void TearDown() override {
        /* Clean up resources after tests */
    }
};

/* Test: Function 1 - Basic test */
TEST_F(ModuleTemplateTest, Function1_BasicTest) {
    s4 result = template_function1(100);
    EXPECT_EQ(100, result);
}

/* Test: Function 1 - Negative value */
TEST_F(ModuleTemplateTest, Function1_NegativeValue) {
    s4 result = template_function1(-50);
    EXPECT_EQ(0, result);
}

/* Test: Function 2 - Basic test */
TEST_F(ModuleTemplateTest, Function2_BasicTest) {
    u1 test_data[4] = {1, 2, 3, 4};
    u4 result = template_function2(test_data, 4);
    EXPECT_EQ(4, result);
}

/* Test: Function 2 - Empty data */
TEST_F(ModuleTemplateTest, Function2_EmptyData) {
    u1 test_data[1];
    u4 result = template_function2(test_data, 0);
    EXPECT_EQ(0, result);
}

/* Test: Function 2 - NULL pointer */
TEST_F(ModuleTemplateTest, Function2_NullPointer) {
    u4 result = template_function2(NULL, 4);
    EXPECT_EQ(0, result);
}
