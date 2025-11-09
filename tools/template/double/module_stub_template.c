/**
 * @file module_stub.c
 * @brief FFF Stubs for module_template external functions
 */

#include "module_template.h"

/* FFFフレームワークをインクルード */
#define DEFINE_FFF_GLOBALS
#include "fff.h"

/* 外部関数のスタブを宣言（必要に応じて） */
/* 例： */
/* FAKE_VALUE_FUNC2(u4, external_function, u1*, u4); */

/* このモジュールが外部関数に依存する場合、ここで宣言します。
 * 必要に応じてコメントを外して修正してください：
 *
 * FAKE_VALUE_FUNC2(u4, external_mem_write, u1*, u4);
 * 
 * その後、テストファイルで：
 * extern "C" {
 *     #include "module_template.h"
 *     #define DEFINE_FFF_GLOBALS
 *     #include "fff.h"
 *     FAKE_VALUE_FUNC2(u4, external_mem_write, u1*, u4);
 * }
 */
