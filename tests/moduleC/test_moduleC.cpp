#include <gtest/gtest.h>
#include <cstdint>
#include "../../target/inc/common.h"

// FFF setup for u4g_mem_wirte
#include "../../fff/fff.h"

DEFINE_FFF_GLOBALS;

// Declare fake in C linkage to match the C implementation
extern "C" {
    FAKE_VALUE_FUNC2(u4, u4g_mem_wirte, u1*, u4);
}

// Now include the header and implementation
#include "../../target/jchg/moduleC/moduleC.h"
#include "../../target/jchg/moduleC/moduleC.c"

// Test for moduleC_integrate
TEST(ModuleCTest, IntegrateBasic)
{
    // 加重平均: (60*100 + 40*0)/100 = 60
    EXPECT_EQ(60, moduleC_integrate(100, 0));
    // 加重平均: (60*0 + 40*100)/100 = 40
    EXPECT_EQ(40, moduleC_integrate(0, 100));
    // 加重平均: (60*50 + 40*50)/100 = 50
    EXPECT_EQ(50, moduleC_integrate(50, 50));
}

TEST(ModuleCTest, IntegrateWeightedAverage)
{
    // valueA: 100, valueB: 50 => (100*60 + 50*40)/100 = 80
    EXPECT_EQ(80, moduleC_integrate(100, 50));
    // valueA: 50, valueB: 100 => (50*60 + 100*40)/100 = 70
    EXPECT_EQ(70, moduleC_integrate(50, 100));
}

TEST(ModuleCTest, IntegrateNegativeValues)
{
    // 負の値も処理できることをテスト
    EXPECT_EQ(-10, moduleC_integrate(-50, 50));
    EXPECT_EQ(10, moduleC_integrate(50, -50));
}

// Test for moduleC_validate
TEST(ModuleCTest, ValidateWithinRange)
{
    // 有効な範囲（0-100）内の値
    EXPECT_EQ(1, moduleC_validate(0));
    EXPECT_EQ(1, moduleC_validate(50));
    EXPECT_EQ(1, moduleC_validate(100));
}

TEST(ModuleCTest, ValidateOutOfRange)
{
    // 範囲外の値
    EXPECT_EQ(0, moduleC_validate(-1));
    EXPECT_EQ(0, moduleC_validate(101));
    EXPECT_EQ(0, moduleC_validate(-100));
    EXPECT_EQ(0, moduleC_validate(200));
}

// Test for moduleC_normalize
TEST(ModuleCTest, NormalizeWithinRange)
{
    // 範囲内の値はそのまま
    EXPECT_EQ(50, moduleC_normalize(50, 0, 100));
    EXPECT_EQ(0, moduleC_normalize(0, 0, 100));
    EXPECT_EQ(100, moduleC_normalize(100, 0, 100));
}

TEST(ModuleCTest, NormalizeBelowMin)
{
    // 最小値より小さい値は最小値に正規化
    EXPECT_EQ(10, moduleC_normalize(5, 10, 100));
    EXPECT_EQ(0, moduleC_normalize(-50, 0, 100));
    EXPECT_EQ(20, moduleC_normalize(10, 20, 80));
}

TEST(ModuleCTest, NormalizeAboveMax)
{
    // 最大値より大きい値は最大値に正規化
    EXPECT_EQ(100, moduleC_normalize(150, 0, 100));
    EXPECT_EQ(80, moduleC_normalize(200, 0, 80));
    EXPECT_EQ(50, moduleC_normalize(100, 10, 50));
}

TEST(ModuleCTest, NormalizeCustomRange)
{
    // カスタム範囲でのテスト
    EXPECT_EQ(30, moduleC_normalize(25, 30, 70));
    EXPECT_EQ(70, moduleC_normalize(100, 30, 70));
    EXPECT_EQ(50, moduleC_normalize(50, 30, 70));
}

// Integration Test: Integrate -> Validate -> Normalize
TEST(ModuleCTest, IntegrationWorkflow)
{
    // moduleA: 100, moduleB: 0 => integrate = 60
    int integrated = moduleC_integrate(100, 0);
    EXPECT_EQ(60, integrated);

    // validate: 60は範囲内(0-100)
    EXPECT_EQ(1, moduleC_validate(integrated));

    // normalize: 60は範囲内(0-100)なのでそのまま
    EXPECT_EQ(60, moduleC_normalize(integrated, 0, 100));
}

TEST(ModuleCTest, IntegrationWithBoundaryNormalization)
{
    // moduleA: 150, moduleB: 100
    // integrate = (150*60 + 100*40)/100 = 130
    int integrated = moduleC_integrate(150, 100);
    EXPECT_EQ(130, integrated);

    // validate: 130は範囲外(0-100)
    EXPECT_EQ(0, moduleC_validate(integrated));

    // normalize: 130を100以下に正規化
    EXPECT_EQ(100, moduleC_normalize(integrated, 0, 100));
}

// Test for moduleC_write_data with fff stub
TEST(ModuleCTest, WriteDataSuccess)
{
    // Setup
    u1 test_data[] = {0x01, 0x02, 0x03, 0x04};
    u4 data_length = 4;
    u4 expected_return = 4;

    // Reset fake before test
    RESET_FAKE(u4g_mem_wirte);

    // Configure the fake function to return the expected value
    u4g_mem_wirte_fake.return_val = expected_return;

    // Call the function
    u4 result = moduleC_write_data(test_data, data_length);

    // Verify
    EXPECT_EQ(expected_return, result);
    EXPECT_EQ(1, u4g_mem_wirte_fake.call_count);
    EXPECT_EQ((uintptr_t)test_data, (uintptr_t)u4g_mem_wirte_fake.arg0_val);
    EXPECT_EQ(data_length, u4g_mem_wirte_fake.arg1_val);
}

TEST(ModuleCTest, WriteDataPartialSuccess)
{
    // Setup - simulate partial write
    u1 test_data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    u4 data_length = 4;
    u4 expected_return = 2;  // Only 2 bytes written

    // Reset fake before test
    RESET_FAKE(u4g_mem_wirte);

    // Configure the fake function
    u4g_mem_wirte_fake.return_val = expected_return;

    // Call the function
    u4 result = moduleC_write_data(test_data, data_length);

    // Verify
    EXPECT_EQ(expected_return, result);
    EXPECT_EQ(1, u4g_mem_wirte_fake.call_count);
}

TEST(ModuleCTest, WriteDataEmptyBuffer)
{
    // Setup - empty data
    u1 test_data[] = {};
    u4 data_length = 0;
    u4 expected_return = 0;

    // Reset fake before test
    RESET_FAKE(u4g_mem_wirte);

    // Configure the fake function
    u4g_mem_wirte_fake.return_val = expected_return;

    // Call the function
    u4 result = moduleC_write_data(test_data, data_length);

    // Verify
    EXPECT_EQ(expected_return, result);
    EXPECT_EQ(1, u4g_mem_wirte_fake.call_count);
}

TEST(ModuleCTest, WriteDataMultipleCalls)
{
    // Setup
    u1 data1[] = {0x11, 0x22};
    u1 data2[] = {0x33, 0x44, 0x55};

    // First call
    RESET_FAKE(u4g_mem_wirte);
    u4g_mem_wirte_fake.return_val = 2;
    u4 result1 = moduleC_write_data(data1, 2);
    EXPECT_EQ(2, result1);

    // Second call - reset and configure fake
    RESET_FAKE(u4g_mem_wirte);
    u4g_mem_wirte_fake.return_val = 3;
    u4 result2 = moduleC_write_data(data2, 3);
    EXPECT_EQ(3, result2);

    // Verify second call
    EXPECT_EQ(1, u4g_mem_wirte_fake.call_count);
}
