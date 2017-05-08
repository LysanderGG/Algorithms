#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <gg.h>

//#define GG_LIST_USE_TAIL

typedef struct ggListNode {
	void*				value;
	struct ggListNode*	next;
} ggListNode;

struct ggList {
	ggListNode*		head;
#ifdef GG_LIST_USE_TAIL
	ggListNode*		tail;
#endif
};


void			ggListInitialize(ggList* _this);
void			ggListFinalize(ggList* _this);

/* Number of items in the list. O(n) - could be done in O(1) if saved. */
uint32_t 		ggListGetSize(const ggList* _this);
/* Return 1 if empty. */
uint32_t 		ggListIsEmpty(const ggList* _this);
/* Return the item at given index, NULL if the index out of bounds. Starts at 0. */
void* 			ggListGetValueAt(const ggList* _this, uint32_t index);
/* Adds an item to the front of the list */
ggResult		ggListPushFront(ggList* _this, void* item);
/* Remove front item and return its value */
void*			ggListPopFront(ggList* _this);
/* Adds an item at the end of the list */
ggResult		ggListPushBack(ggList* _this, void* item);
/* Remove end item and return its value */
void*			ggListPopBack(ggList* _this);
/* Get item of front item */
void*			ggListFront(ggList* _this);
/* Get item of end item */
void*			ggListBack(ggList* _this);
/* Insert value at index, so current item at that index is pointed to by new item at index */
ggResult		ggListInsert(ggList* _this, uint32_t index, void* item);
/* Remove item at given index */
void			ggListErase(ggList* _this, uint32_t index);
/* Return the item at nth position from the end of the list */
void* 			ggListGetValueAtFromEnd(const ggList* _this, uint32_t index);
/* Reverse the list */
void			ggListReverse(ggList* _this);
/* Remove the first item in the list with this value */
void			ggListRemove(ggList* _this, void* item);


#ifdef __cplusplus
}
#endif
