#include <gtest/gtest.h>
#include "../../target/inc/common.h"
#include "../../target/jchg/moduleB/moduleB.h"
#include "../../target/jchg/moduleB/moduleB.c"

/* Test for moduleB_subtract */
TEST(ModuleBTest, SubtractPositiveNumbers) {
    EXPECT_EQ(1, moduleB_subtract(3, 2));
    EXPECT_EQ(0, moduleB_subtract(5, 5));
}

TEST(ModuleBTest, SubtractNegativeNumbers) {
    EXPECT_EQ(-5, moduleB_subtract(-2, 3));
    EXPECT_EQ(1, moduleB_subtract(-2, -3));
}

/* Test for moduleB_divide */
TEST(ModuleBTest, DividePositiveNumbers) {
    EXPECT_EQ(2, moduleB_divide(6, 3));
    EXPECT_EQ(1, moduleB_divide(5, 3));
}

TEST(ModuleBTest, DivideByZero) {
    EXPECT_EQ(0, moduleB_divide(5, 0));
}

TEST(ModuleBTest, DivideNegativeNumbers) {
    EXPECT_EQ(-2, moduleB_divide(-6, 3));
    EXPECT_EQ(2, moduleB_divide(-6, -3));
}
