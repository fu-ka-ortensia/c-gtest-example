#include "module_template.h"
#include <stddef.h>

/* ============================================================================
 * 実装
 * ============================================================================
 */

/**
 * @brief テンプレート関数1
 * @param value 入力値
 * @return 結果
 */
s4 template_function1(s4 value)
{
    if ( value < 0 ) {
        return 0;
    }
    return value;
}

/**
 * @brief テンプレート関数2
 * @param data 入力データポインタ
 * @param length データ長
 * @return 処理されたバイト数
 */
u4 template_function2(u1* data, u4 length)
{
    if ( data == NULL || length == 0 ) {
        return 0;
    }
    /* TODO: ここにロジックを実装してください */
    return length;
}
