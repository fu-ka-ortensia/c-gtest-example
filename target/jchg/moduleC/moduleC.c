#include "../../inc/common.h"
#include "../../inc/u4g_mem.h"
#include "moduleC.h"

// I/F関数：moduleAとmoduleBの結果を統合処理
// valueAとvalueBを加重平均する（60% valueA + 40% valueB）
s4 moduleC_integrate(s4 valueA, s4 valueB)
{
    return (valueA * 60 + valueB * 40) / 100;
}

// I/F関数：計算結果をバリデーション
// 結果が0以上100以下の範囲内かチェック
s4 moduleC_validate(s4 result)
{
    if (result < 0 || result > 100) {
        return 0;  // バリデーション失敗
    }
    return 1;  // バリデーション成功
}

// I/F関数：結果を正規化（範囲内に収める）
// 指定された範囲内に値を収める
s4 moduleC_normalize(s4 value, s4 min, s4 max)
{
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

u4 moduleC_write_data(u1* data, u4 length)
{
    u4 u4t_ret;

    u4t_ret = u4g_mem_wirte(data, length);

    return u4t_ret;
}