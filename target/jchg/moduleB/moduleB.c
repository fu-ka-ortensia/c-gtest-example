#include "../../inc/common.h"
#include "moduleB.h"

s4 moduleB_subtract(s4 a, s4 b)
{
    return a - b;
}

s4 moduleB_divide(s4 a, s4 b)
{
    if ( b == 0 ) return 0;
    return a / b;
}
