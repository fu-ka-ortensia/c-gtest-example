/* External module stubs for testing */
#include "../../target/inc/common.h"
#include "../../target/inc/u4g_mem.h"
#include "../../fff/fff.h"

DEFINE_FFF_GLOBALS;

/* Define fake function for u4g_mem_wirte (2 arguments: u1* data, u4 length) */
FAKE_VALUE_FUNC2(u4, u4g_mem_wirte, u1*, u4);
