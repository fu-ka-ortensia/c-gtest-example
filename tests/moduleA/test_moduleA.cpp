#include <gtest/gtest.h>
#include "../../target/inc/common.h"
#include "../../target/jchg/moduleA/moduleA.h"
#include "../../target/jchg/moduleA/moduleA.c"

// Test for moduleA_add
TEST(ModuleATest, AddPositiveNumbers) {
    EXPECT_EQ(5, moduleA_add(2, 3));
    EXPECT_EQ(0, moduleA_add(0, 0));
}

TEST(ModuleATest, AddNegativeNumbers) {
    EXPECT_EQ(-5, moduleA_add(-2, -3));
    EXPECT_EQ(1, moduleA_add(-2, 3));
}

// Test for moduleA_multiply
TEST(ModuleATest, MultiplyPositiveNumbers) {
    EXPECT_EQ(6, moduleA_multiply(2, 3));
    EXPECT_EQ(0, moduleA_multiply(0, 5));
}

TEST(ModuleATest, MultiplyNegativeNumbers) {
    EXPECT_EQ(6, moduleA_multiply(-2, -3));
    EXPECT_EQ(-6, moduleA_multiply(-2, 3));
}
