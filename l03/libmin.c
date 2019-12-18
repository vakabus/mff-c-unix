#include "libmin.h"
#include<assert.h>


int32_t min(int32_t a[], size_t len) {
    // requires at least one element in the array
    assert(len > 0);

    int32_t d = a[0];
    for (size_t i = 1; i < len; i++) {
        if (d > a[i])
            d = a[i];
    }

    return d;
}
