#ifndef MODULE_C_H
#define MODULE_C_H

#include "../../inc/common.h"

/* I/F関数：moduleAとmoduleBの結果を統合処理 */
s4 moduleC_integrate(s4 valueA, s4 valueB);

/* I/F関数：計算結果をバリデーション */
s4 moduleC_validate(s4 result);

/* I/F関数：結果を正規化（範囲内に収める） */
s4 moduleC_normalize(s4 value, s4 min, s4 max);

u4 moduleC_write_data(u1* data, u4 length);

#endif /* MODULE_C_H */
