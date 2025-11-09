#ifndef MODULE_TEMPLATE_H
#define MODULE_TEMPLATE_H

#include "common.h"

/* ============================================================================
 * 関数宣言
 * ============================================================================
 */

/**
 * @brief テンプレート関数1
 * @param value 入力値
 * @return 結果
 */
s4 template_function1(s4 value);

/**
 * @brief テンプレート関数2
 * @param data 入力データポインタ
 * @param length データ長
 * @return 処理されたバイト数
 */
u4 template_function2(u1* data, u4 length);

#endif /* MODULE_TEMPLATE_H */
