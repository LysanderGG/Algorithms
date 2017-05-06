#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <gg.h>

struct ggPointerArray {
	void**		array;
	uint32_t	capacity;
	uint32_t	size;
};

/* Initialize an array with a starting capacity. If 0 is given, uses the default capacity (16). */
ggResult		ggPointerArrayInitialize	(ggPointerArray* _this, uint32_t capacity);
void			ggPointerArrayFinalize		(ggPointerArray* _this);

/* Number of items it can hold */
uint32_t 		ggPointerArrayGetCapacity	(const ggPointerArray* _this);
/* Number of items in the array */
uint32_t 		ggPointerArrayGetSize		(const ggPointerArray* _this);
/* Return 1 if empty. */
uint32_t 		ggPointerArrayIsEmpty		(const ggPointerArray* _this);
/* Return the item at given index, NULL if the index out of bounds */
void* 			ggPointerArrayGetItem		(const ggPointerArray* _this, uint32_t index);
/* Insert an item at index, shift that index's value and trailing elements to the right */
ggResult		ggPointerArrayInsert		(ggPointerArray* _this, uint32_t index, void* item);
/* Insert at the end */
ggResult		ggPointerArrayPush			(ggPointerArray* _this, void* item);
/* Insert at the beginning */
ggResult		ggPointerArrayPrepend		(ggPointerArray* _this, void* item);
/* Remove from end, return value */
void*			ggPointerArrayPop			(ggPointerArray* _this);
/* Delete item at index, shifting all trailing elements left */
ggResult		ggPointerArrayDelete		(ggPointerArray* _this, uint32_t index);
/* Look for value and remove index holding it (even if in multiple places) */
ggResult		ggPointerArrayRemove		(ggPointerArray* _this, void* item);
/* Look for value and return first index with that value, -1 if not found */
int32_t			ggPointerArrayFind			(const ggPointerArray* _this, void* item);


#ifdef __cplusplus
}
#endif
