/* 外部モジュール：テスト用スタブ */
#include "../../target/inc/common.h"
#include "../../target/inc/u4g_mem.h"
#include "../../fff/fff.h"

DEFINE_FFF_GLOBALS;

/* u4g_mem_wirte 用フェイク関数を定義（引数：u1* data, u4 length） */
FAKE_VALUE_FUNC2(u4, u4g_mem_wirte, u1*, u4);
