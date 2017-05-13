#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <gg.h>
#include <Array.h>

/**
 * Hash Table using linear probing.
 */

typedef uint32_t (*hashFunc_t)(const void* key);
typedef int32_t (*compFunc_t)(const void* a, const void* b);

typedef enum {
	FREE,
	USED,
	DELETED
} ItemStatus;

typedef struct ggHashItem {
	ItemStatus	status;
	uint32_t	hash; // store the hash to avoid recomputation when resizing the hash table.
	const void*	key;
	const void*	value;
} ggHashItem;

struct ggHashTable {
	ggHashItem*		array;
	uint32_t		capacity;
	uint32_t		nbItemsUsed;
	uint32_t		nbItemsNotFree;
	hashFunc_t		hashFunc;
	compFunc_t		compFunc;
};

/* ------------------------------------------------------------------------- */
/* Default hash functions */
uint32_t ggHash_int(const void* key);
uint32_t ggHash_string(const void* key);

/* Default comp functions */
int32_t ggComp_int(const void* a, const void* b);
int32_t ggComp_str(const void* a, const void* b);

/* ------------------------------------------------------------------------- */


ggResult	ggHashTableInitialize	(ggHashTable* _this, hashFunc_t hashFunc, compFunc_t compFunc);
void		ggHashTableFinalize		(ggHashTable* _this);

/* If key already exists, update value */
ggResult	ggHashTableAdd			(ggHashTable* _this, const void* key, const void* value);
/* Return 1 if exists, 0 if not. */
int32_t		ggHashTableExists		(const ggHashTable* _this, const void* key);
/* Return GG_KEY_ERROR if the key does not match any item */
ggResult	ggHashTableGet			(const ggHashTable* _this, const void* key, void** value);
/* Return GG_KEY_ERROR if the key does not match any item */
ggResult	ggHashTableRemove		(ggHashTable* _this, const void* key);


#ifdef __cplusplus
}
#endif
