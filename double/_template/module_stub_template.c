/**
 * @file module_stub.c
 * @brief FFF Stubs for module_template external functions
 */

#include "module_template.h"

/* Include FFF framework */
#define DEFINE_FFF_GLOBALS
#include "fff.h"

/* Declare stubs for external functions if needed */
// Example:
// FAKE_VALUE_FUNC2(u4, external_function, u1*, u4);

/* If this module depends on external functions, declare them here.
 * Uncomment and modify as needed:
 *
 * FAKE_VALUE_FUNC2(u4, external_mem_write, u1*, u4);
 * 
 * Then in your test file:
 * extern "C" {
 *     #include "module_template.h"
 *     #define DEFINE_FFF_GLOBALS
 *     #include "fff.h"
 *     FAKE_VALUE_FUNC2(u4, external_mem_write, u1*, u4);
 * }
 */
