#ifndef MODULE_C_H
#define MODULE_C_H

#include "../../inc/common.h"

/**
 * @brief moduleAとmoduleBの結果を統合処理します
 * @param valueA moduleAからの値
 * @param valueB moduleBからの値
 * @return 統合処理後の結果
 */
s4 moduleC_integrate(s4 valueA, s4 valueB);

/**
 * @brief 計算結果をバリデーション（検証）します
 * @param result 検証する結果値
 * @return バリデーション後の値
 */
s4 moduleC_validate(s4 result);

/**
 * @brief 結果を正規化（指定範囲内に収める）します
 * @param value 正規化する値
 * @param min 最小値
 * @param max 最大値
 * @return 正規化後の値
 */
s4 moduleC_normalize(s4 value, s4 min, s4 max);

/**
 * @brief メモリにデータを書き込みます
 * @param data データバッファへのポインタ
 * @param length データの長さ
 * @return 書き込まれたバイト数
 */
u4 moduleC_write_data(u1* data, u4 length);

#endif /* MODULE_C_H */
