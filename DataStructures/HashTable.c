#include <HashTable.h>
#include <gg.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------- */

#define GG_HASHTABLE_DEFAULT_CAPACITY 53

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

ggResult
ggHashTableInitialize(ggHashTable* _this, hashFunc_t hashFunc, compFunc_t compFunc)
{
	ggAssert(_this);
	ggAssert(hashFunc);

	_this->array = malloc(GG_HASHTABLE_DEFAULT_CAPACITY * sizeof(ggHashItem));
	GG_CONDITION(!_this->array, GG_OUT_OF_MEMORY);

	_this->capacity = GG_HASHTABLE_DEFAULT_CAPACITY;
	_this->nbItems = 0;
	_this->hashFunc = hashFunc;
	_this->compFunc = compFunc;

	/* Could use a memset or calloc but do it explicitly for clarity. */
	for( uint32_t i = 0; i < _this->capacity; ++i )
	{
		_this->array[i].status = FREE;
		_this->array[i].hash = 0;
		_this->array[i].key = NULL;
		_this->array[i].value = NULL;
	}

	return GG_OK;
}

void
ggHashTableFinalize(ggHashTable* _this)
{
	ggAssert(_this);

	free(_this->array);
	_this->capacity = 0;
	_this->nbItems = 0;
}

ggResult
ggHashTableAdd(ggHashTable* _this, const void* key, const void* value)
{
	ggAssert(_this);

	// TODO: add load factor
	// TODO: resize if necessary

	uint32_t hash = _this->hashFunc(key);
	uint32_t reducedHash = hash % _this->capacity;
	ggHashItem* item = _this->array + reducedHash;

	for( uint32_t i = reducedHash; i < _this->capacity && item->status == USED; ++i, item = _this->array + i );
	if( item->status == USED )
	{
		item = _this->array;
		for( uint32_t i = 0; i < reducedHash && item->status == USED; ++i, item = _this->array + i );
	}

	/* Should not happen as the hash table must have been resized earlier if nearly full. */
	ggAssert(item->status != USED);
	
	item->status = USED;
	item->hash = hash;
	item->key = key;
	item->value = value;

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

	return GG_OK;
}

/* ------------------------------------------------------------------------- */
