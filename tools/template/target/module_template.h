#ifndef MODULE_TEMPLATE_H
#define MODULE_TEMPLATE_H

#include "common.h"

/* ============================================================================
 * Function Declarations
 * ============================================================================
 */

/**
 * @brief Template function 1
 * @param value Input value
 * @return Result
 */
s4 template_function1(s4 value);

/**
 * @brief Template function 2
 * @param data Input data pointer
 * @param length Data length
 * @return Number of processed bytes
 */
u4 template_function2(u1* data, u4 length);

#endif /* MODULE_TEMPLATE_H */
