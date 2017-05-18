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

/* ------------------------------------------------------------------------- */

typedef enum ggResult {
	GG_OK = 0,
	GG_OUT_OF_MEMORY,
	GG_KEY_ERROR
} ggResult;

/* ------------------------------------------------------------------------- */

typedef struct ggPointerArray ggPointerArray;
typedef struct ggHashTable ggHashTable;
typedef struct ggList ggList;
typedef struct ggBST ggBST;

/* ------------------------------------------------------------------------- */

typedef uint32_t(*hashFunc_t)(const void* key);
/* Must return 0 if a == b, 1 if a > b, -1 if a < b. */
typedef int32_t(*compFunc_t)(const void* a, const void* b);

/* ------------------------------------------------------------------------- */
/* Default comp functions */
int32_t ggComp_int(const void* a, const void* b);
int32_t ggComp_str(const void* a, const void* b);

/* ------------------------------------------------------------------------- */

#ifdef __cplusplus
}
#endif
