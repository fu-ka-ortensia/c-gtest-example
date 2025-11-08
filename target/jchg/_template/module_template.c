#include "module_template.h"
#include <stddef.h>

/* ============================================================================
 * Implementation
 * ============================================================================
 */

/**
 * @brief Template function 1
 * @param value Input value
 * @return Result
 */
s4 template_function1(s4 value) {
    if (value < 0) {
        return 0;
    }
    return value;
}

/**
 * @brief Template function 2
 * @param data Input data pointer
 * @param length Data length
 * @return Number of processed bytes
 */
u4 template_function2(u1* data, u4 length) {
    if (data == NULL || length == 0) {
        return 0;
    }
    // TODO: Implement your logic here
    return length;
}
