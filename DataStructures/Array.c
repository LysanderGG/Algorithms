#include "Array.h"
#include <gg.h>
#include <stdlib.h>


ggResult
ggPointerArrayInitialize(ggPointerArray* _this, uint32_t capacity)
{
	ggAssert(_this);

	if(capacity == 0) { capacity = 16; }

	_this->array = malloc(capacity * sizeof(void*));
	GG_CONDITION(!_this->array, GG_OUT_OF_MEMORY);

	_this->capacity = capacity;
	_this->size = 0;

	return GG_OK;
}

void
ggPointerArrayFinalize(ggPointerArray* _this)
{
	ggAssert(_this);
	free(_this->array);
	_this->capacity = 0;
	_this->size = 0;
}

static ggResult
_ggPointerArrayExpand(ggPointerArray* _this)
{
	// TODO
	return GG_OK;
}

static ggResult
_ggPointerArrayShrink(ggPointerArray* _this)
{
	// TODO
	return GG_OK;
}

uint32_t
ggPointerArrayGetCapacity(const ggPointerArray* _this)
{
	ggAssert(_this);
	return _this->capacity;
}

uint32_t
ggPointerArrayGetSize(const ggPointerArray* _this)
{
	ggAssert(_this);
	return _this->size;
}

uint32_t
ggPointerArrayIsEmpty(const ggPointerArray* _this)
{
	return ggPointerArrayGetSize(_this) != 0;
}

void*
ggPointerArrayGetItem(const ggPointerArray* _this, uint32_t index)
{
	ggAssert(_this);
	if( index >= _this->size ) {
		return NULL;
	}

	return _this->array[index];
}

ggResult
ggPointerArrayInsert(ggPointerArray* _this, uint32_t index, void* item)
{
	ggAssert(_this);

	if( index > _this->size ) {
		index = _this->size;
	}

	if( _this->size == _this->capacity ) {
		ggResult eRes = _ggPointerArrayExpand(_this);
		GG_CONDITION(GG_OK != eRes, eRes);
	}

	for( uint32_t i = _this->size; i > index; --i )
	{
		_this->array[i] = _this->array[i - 1];
	}
	_this->array[index] = item;
	++_this->size;

	return GG_OK;
}

ggResult
ggPointerArrayPush(ggPointerArray* _this, void* item)
{
	return ggPointerArrayInsert(_this, _this->size, item);
}

ggResult
ggPointerArrayPrepend(ggPointerArray* _this, void* item)
{
	return ggPointerArrayInsert(_this, 0, item);
}

void*
ggPointerArrayPop(ggPointerArray* _this)
{
	void* res = _this->array[_this->size - 1];
	--_this->size;

	_ggPointerArrayShrink(_this); /* ignore ggResult */

	return res;
}

ggResult
ggPointerArrayDelete(ggPointerArray* _this, uint32_t index)
{
	ggAssert(_this);
	ggAssert(index < _this->size);

	for( uint32_t i = index; i < _this->size; ++i )
	{
		_this->array[i] = _this->array[i + 1];
	}
	--_this->size;

	return _ggPointerArrayShrink(_this);
}

ggResult
ggPointerArrayRemove(ggPointerArray* _this, void* item)
{
	ggAssert(_this);
	int offset = 0;
	for( uint32_t i = 0; i < _this->size; ++i )
	{
		if( _this->array[i] == item )
		{
			++offset;
		}
		_this->array[i] = _this->array[i + offset];
	}
	_this->size -= offset;

	return _ggPointerArrayShrink(_this);
}

int32_t
ggPointerArrayFind(const ggPointerArray* _this, void* item)
{
	ggAssert(_this);
	for( uint32_t i = 0; i < _this->size; ++i ) {
		if( _this->array[i] == item ) {
			return i;
		}
	}
	return -1;
}
