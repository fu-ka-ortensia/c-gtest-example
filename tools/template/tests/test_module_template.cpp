#include <gtest/gtest.h>

extern "C" {
    #include "module_template.h"
}

class ModuleTemplateTest : public ::testing::Test {
protected:
    void SetUp() override {
        /* テスト用のリソースを初期化 */
    }

    void TearDown() override {
        /* テスト後にリソースをクリーンアップ */
    }
};

/* テスト：関数1 - 基本テスト */
TEST_F(ModuleTemplateTest, Function1_BasicTest) {
    s4 result = template_function1(100);
    EXPECT_EQ(100, result);
}

/* テスト：関数1 - 負の値 */
TEST_F(ModuleTemplateTest, Function1_NegativeValue) {
    s4 result = template_function1(-50);
    EXPECT_EQ(0, result);
}

/* テスト：関数2 - 基本テスト */
TEST_F(ModuleTemplateTest, Function2_BasicTest) {
    u1 test_data[4] = {1, 2, 3, 4};
    u4 result = template_function2(test_data, 4);
    EXPECT_EQ(4, result);
}

/* テスト：関数2 - 空のデータ */
TEST_F(ModuleTemplateTest, Function2_EmptyData) {
    u1 test_data[1];
    u4 result = template_function2(test_data, 0);
    EXPECT_EQ(0, result);
}

/* テスト：関数2 - NULLポインタ */
TEST_F(ModuleTemplateTest, Function2_NullPointer) {
    u4 result = template_function2(NULL, 4);
    EXPECT_EQ(0, result);
}
