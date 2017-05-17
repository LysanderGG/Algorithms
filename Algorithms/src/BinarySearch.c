#include <BinarySearch.h>

int32_t	
ggBinarySearch(void** array, uint32_t size, compFunc_t compFunc, void* item)
{
	ggAssert(array && compFunc);
	ggAssert(size > 0);

	uint32_t leftIdx = 0, rightIdx = size;
	while( leftIdx <= rightIdx )
	{
		uint32_t idx = leftIdx + (rightIdx - leftIdx) / 2;
		int32_t res = compFunc(item, array[idx]);
		if( res == 0 )
		{
			return idx;
		}
		else if( res > 0 )
		{
			leftIdx = idx + 1;
		}
		else
		{
			rightIdx = idx - 1;
		}
	}

	return -1;
}
