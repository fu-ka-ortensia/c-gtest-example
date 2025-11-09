#ifndef __U4G_MEM_H__
#define __U4G_MEM_H__

#include "common.h"

/* 外部モジュール：メモリ書き込み関数 */
/* @param data: データバッファへのポインタ */
/* @param length: 書き込むバイト数 */
/* @return: 書き込まれたバイト数 */
u4 u4g_mem_wirte(u1* data, u4 length);

#endif /* __U4G_MEM_H__ */
