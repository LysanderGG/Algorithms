#include <HashTable.h>
#include <gg.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------- */

#define GG_HASHTABLE_DEFAULT_CAPACITY 17

/* ------------------------------------------------------------------------- */

uint32_t 
ggHash_int(const void* key)
{
	return (uint32_t)key;
}

uint32_t
ggHash_string(const void* key)
{
	uint32_t hash = 5381;
	uint32_t c;
	const char *str = key;

	while( c = *str++ ) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash;
}

int32_t ggComp_int(const void* a, const void* b)
{
	return a > b ? 1 : a < b ? -1 : 0;
}

int32_t ggComp_str(const void* a, const void* b)
{
	return strcmp(a, b);
}

/* ------------------------------------------------------------------------- */

static void 
_ggHashTableInitializeArray(ggHashItem* array, uint32_t size)
{
	/* Could use a memset or calloc but do it explicitly for clarity. */
	for( uint32_t i = 0; i < size; ++i )
	{
		array[i].status = FREE;
		array[i].hash = 0;
		array[i].key = NULL;
		array[i].value = NULL;
	}
}

ggResult
ggHashTableInitialize(ggHashTable* _this, hashFunc_t hashFunc, compFunc_t compFunc)
{
	ggAssert(_this);
	ggAssert(hashFunc);

	_this->array = malloc(GG_HASHTABLE_DEFAULT_CAPACITY * sizeof(ggHashItem));
	GG_CONDITION(!_this->array, GG_OUT_OF_MEMORY);

	_this->capacity = GG_HASHTABLE_DEFAULT_CAPACITY;
	_this->nbItemsUsed = 0;
	_this->nbItemsNotFree = 0;
	_this->hashFunc = hashFunc;
	_this->compFunc = compFunc;

	_ggHashTableInitializeArray(_this->array, _this->capacity);

	return GG_OK;
}

void
ggHashTableFinalize(ggHashTable* _this)
{
	ggAssert(_this);

	free(_this->array);
	_this->capacity = 0;
	_this->nbItemsUsed = 0;
	_this->nbItemsNotFree = 0;
}

/* ------------------------------------------------------------------------- */

static void
_ggHashTableAddItem(ggHashTable* _this, const void* key, const void* value, uint32_t hash)
{
	ggAssert(_this);

	uint32_t reducedHash = hash % _this->capacity;
	ggHashItem* item = _this->array + reducedHash;

	for( uint32_t i = reducedHash + 1; i < _this->capacity && item->status == USED; ++i )
	{
		item = _this->array + i;
	}
	if( item->status == USED )
	{
		item = _this->array;
		for( uint32_t i = 0; i < reducedHash && item->status == USED; ++i )
		{
			item = _this->array + i;
		}
	}

	/* Should not happen as the hash table must have been resized earlier if nearly full. */
	ggAssert(item->status != USED);

	item->status = USED;
	item->hash = hash;
	item->key = key;
	item->value = value;

	++_this->nbItemsUsed;
	++_this->nbItemsNotFree;
}

static ggResult
_ggHashTableResize(ggHashTable* _this, uint32_t newCapacity)
{
	ggAssert(_this);
	ggHashItem* newArray = malloc(newCapacity * sizeof(ggHashItem));
	GG_CONDITION(!newArray, GG_OUT_OF_MEMORY);

	ggHashItem* oldArray = _this->array;
	uint32_t oldCapacity = _this->capacity;

	_this->array = newArray;
	_this->capacity = newCapacity;
	_this->nbItemsUsed = 0;
	_this->nbItemsNotFree = 0;

	_ggHashTableInitializeArray(newArray, newCapacity);

	for( uint32_t i = 0; i < oldCapacity; ++i )
	{
		ggHashItem item = oldArray[i];
		if( item.status == USED )
		{
			_ggHashTableAddItem(_this, item.key, item.value, item.hash);
		}
	}
	free(oldArray);

	return GG_OK;
}

static ggResult
_ggHashTableExpand(ggHashTable* _this)
{
	ggAssert(_this);

	uint32_t newCapacity = _this->capacity * 2; // Todo: next prime
	return _ggHashTableResize(_this, newCapacity);
}

static ggResult
_ggHashTableShrink(ggHashTable* _this)
{
	ggAssert(_this);

	uint32_t newCapacity = _this->capacity / 2; // Todo: next prime
	return _ggHashTableResize(_this, newCapacity);
}


ggResult
ggHashTableAdd(ggHashTable* _this, const void* key, const void* value)
{
	ggAssert(_this);

	if( _this->nbItemsNotFree > _this->capacity * 2 / 3 )
	{
		_ggHashTableExpand(_this);
	}

	uint32_t hash = _this->hashFunc(key);
	_ggHashTableAddItem(_this, key, value, hash);

	return GG_OK;
}

/* Return the index of the key in _this->array if found, -1 if not. */
static int32_t 
_ggHashTableGetIndex(const ggHashTable* _this, const void* key)
{
	uint32_t hash = _this->hashFunc(key);
	uint32_t reducedHash = hash % _this->capacity;
	ggHashItem* item = _this->array + reducedHash;
	uint32_t i = reducedHash;

	while( i < _this->capacity )
	{
		item = _this->array + i;
		if( item->status == USED 
		 && item->hash == hash 
		 && _this->compFunc(item->key, key) == 0 )
		{
			return i;
		}
		++i;
	}

	i = 0;
	while( i < reducedHash )
	{
		item = _this->array + i;
		if( item->status == USED
			&& item->hash == hash
			&& _this->compFunc(item->key, key) == 0 )
		{
			return i;
		}
		++i;
	}

	return -1;
}

int32_t
ggHashTableExists(const ggHashTable* _this, const void* key)
{
	ggAssert(_this);
	void* value = NULL;
	ggResult res = ggHashTableGet(_this, key, &value);
	GG_UNUSED(value);
	return res == GG_OK;
}

ggResult
ggHashTableGet(const ggHashTable* _this, const void* key, const void** value)
{
	ggAssert(_this);
	ggAssert(value);

	int32_t idx = _ggHashTableGetIndex(_this, key);
	if( idx < 0 ) {
		return GG_KEY_ERROR;
	}

	*value = _this->array[idx].value;

	return GG_OK;
}

ggResult
ggHashTableRemove(ggHashTable* _this, const void* key)
{
	ggAssert(_this);

	int32_t idx = _ggHashTableGetIndex(_this, key);
	if( idx < 0 ) {
		return GG_KEY_ERROR;
	}

	_this->array[idx].status = DELETED;
	--_this->nbItemsUsed;

	if( _this->capacity > GG_HASHTABLE_DEFAULT_CAPACITY && _this->nbItemsUsed < _this->capacity / 4 )
	{
		_ggHashTableShrink(_this);
	}

	return GG_OK;
}

/* ------------------------------------------------------------------------- */
