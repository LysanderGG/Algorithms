#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>

#ifndef NULL
#define NULL 0
#endif

#define ggAssert(_cond) assert(_cond)

#define GG_UNUSED(x) (void)(x)

#define GG_CONDITION(_cond, _ret) do { if(_cond) { return _ret; } } while(0)

typedef enum ggResult {
	GG_OK = 0,
	GG_OUT_OF_MEMORY,
	GG_KEY_ERROR
} ggResult;


typedef struct ggPointerArray ggPointerArray;
typedef struct ggHashTable ggHashTable;
typedef struct ggList ggList;

#ifdef __cplusplus
}
#endif
