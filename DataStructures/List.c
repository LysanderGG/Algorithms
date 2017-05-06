#include "List.h"
#include <gg.h>
#include <stdlib.h>

static ggListNode* 
_ggListGetLastNode(ggList* _this)
{
	ggAssert(_this);

#ifdef GG_LIST_USE_TAIL
	return _this->tail;
#else
	ggListNode* node = _this->head;
	while( node && node->next )
	{
		node = node->next;
	}
	return node;
#endif
}

void*
_ggListGetNodeAt(const ggList* _this, uint32_t index)
{
	ggAssert(_this);

	ggListNode* node = _this->head;
	while( node && index > 0 )
	{
		--index;
		node = node->next;
	}

	return node;
}

/* ------------------------------------------------------------------------- */

void
ggListInitialize(ggList* _this)
{
	ggAssert(_this);

	_this->head = NULL;
#ifdef GG_LIST_USE_TAIL
	_this->tail = NULL;
#endif
}

void
ggListFinalize(ggList* _this)
{
	ggAssert(_this);
	
	ggListNode* node = _this->head;
	while( node )
	{
		ggListNode* next = node->next;
		free(node);
		node = next;
	}

	_this->head = NULL;
#ifdef GG_LIST_USE_TAIL
	_this->tail = NULL;
#endif
}

uint32_t
ggListGetSize(const ggList* _this)
{
	ggAssert(_this);

	uint32_t size = 0;
	ggListNode* node = _this->head;
	while( node )
	{
		++size;
		node = node->next;
	}

	return size;
}

uint32_t
ggListIsEmpty(const ggList* _this)
{
	ggAssert(_this);
	return NULL == _this->head;
}

void*
ggListGetValueAt(const ggList* _this, uint32_t index)
{
	ggAssert(_this);
	ggListNode* node = _ggListGetNodeAt(_this, index);
	return node ? node->value : NULL;
}

ggResult
ggListPushFront(ggList* _this, void* item)
{
	ggAssert(_this);

	ggListNode* newItem = malloc(sizeof(ggListNode));
	GG_CONDITION(!newItem, GG_OUT_OF_MEMORY);

	newItem->value = item;
	newItem->next = _this->head;
	_this->head = newItem;

	return GG_OK;
}

void*
ggListPopFront(ggList* _this)
{
	ggAssert(_this);

	void* ret = NULL;

	if( _this->head )
	{
		ret = _this->head->value;
		void* next = _this->head->next;
		
		free(_this->head);

		_this->head = next;
	}

	return ret;
}

ggResult
ggListPushBack(ggList* _this, void* item)
{
	ggAssert(_this);

	ggListNode* newItem = malloc(sizeof(ggListNode));
	GG_CONDITION(!newItem, GG_OUT_OF_MEMORY);

	newItem->value = item;
	newItem->next = NULL;

	ggListNode* lastNode = _ggListGetLastNode(_this);
	if( lastNode )
	{
		lastNode->next = newItem;
	}
	else
	{
		_this->head = newItem;
	}

	return GG_OK;
}

void*
ggListPopBack(ggList* _this)
{
	ggAssert(_this);

	ggListNode* node = _this->head;
	ggListNode* prevNode = NULL;
	while( node && node->next )
	{
		prevNode = node;
		node = node->next;
	}

	void* ret = NULL;
	if( node )
	{
		ret = node->value;
		if( prevNode )
		{
			prevNode->next = NULL;
		}
		else
		{
			/* no prevNode means that it is the only item in the list. */
			_this->head = NULL;
		}

		free(node);
	}

	return ret;
}

void*
ggListFront(ggList* _this)
{
	ggAssert(_this);
	return _this->head ? _this->head->value : NULL;
}

void*
ggListBack(ggList* _this)
{
	ggAssert(_this);
	ggListNode* lastNode = _ggListGetLastNode(_this);
	return lastNode ? lastNode->value : NULL;
}

ggResult
ggListInsert(ggList* _this, uint32_t index, void* item)
{
	ggAssert(_this);
	ggAssert(index <= ggListGetSize(_this));

	ggListNode* prevNode = (index > 0) ? _ggListGetNodeAt(_this, index - 1) : NULL;
	ggListNode* nextNode = prevNode ? prevNode->next : _ggListGetNodeAt(_this, index);
	ggListNode* newNode = malloc(sizeof(ggListNode));
	GG_CONDITION(!newNode, GG_OUT_OF_MEMORY);

	newNode->value = item;
	newNode->next = nextNode;

	if( index == 0 )
	{
		_this->head = newNode;
	}
	else
	{
		prevNode->next = newNode;
	}

	return GG_OK;
}

void
ggListErase(ggList* _this, uint32_t index)
{
	ggAssert(_this);
	ggAssert(index < ggListGetSize(_this));

	ggListNode* prevNode = (index > 0) ? _ggListGetNodeAt(_this, index - 1) : NULL;
	ggListNode* node = prevNode ? prevNode->next : _ggListGetNodeAt(_this, index);

	if( node )
	{
		if( prevNode )
		{
			prevNode->next = node->next;
		}
		free(node);
	}
}

void*
ggListGetValueAtFromEnd(const ggList* _this, uint32_t index)
{
	ggAssert(_this);
	uint32_t fromStartIndex = ggListGetSize(_this) - index - 1;
	return ggListGetValueAt(_this, fromStartIndex);
}

void
ggListReverse(ggList* _this)
{
	ggAssert(_this);

	ggListNode* n1 = _this->head;
	ggListNode* n2 = n1->next;

	while( n1 && n2 )
	{
		ggListNode* next = n2->next;

		n2->next = n1;
		n1 = n2;
		n2 = next;
	}
}

void
ggListRemove(ggList* _this, void* item)
{
	ggAssert(_this);

	ggListNode* node = _this->head;
	ggListNode* prevNode = NULL;
	while( node && node->value != item )
	{
		prevNode = node;
		node = node->next;
	}

	if( node )
	{
		if( prevNode )
		{
			prevNode->next = node->next;
		}
		free(node);
	}
}
