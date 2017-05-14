#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <gg.h>

/* array must be sorted when calling this function. */
int32_t	ggBinarySearch(void** array, uint32_t size, compFunc_t compFunc, void* item);


#ifdef __cplusplus
}
#endif
