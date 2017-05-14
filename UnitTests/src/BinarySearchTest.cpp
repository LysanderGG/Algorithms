#include "gtest/gtest.h"
#include <BinarySearch.h>

class BinarySearchTest : public ::testing::Test 
{

public:
	BinarySearchTest()
	{
	}
	
	virtual ~BinarySearchTest()
	{
	}
};

TEST_F(BinarySearchTest, Int)
{
	int32_t arr[] = {1,2,3,5,6,9,10,11,12,15,20,21};
	uint32_t size = sizeof(arr) / sizeof(*arr);
	
	for( uint32_t i = 0; i < size; ++i )
	{
		for( uint32_t j = i + 1; j <= size; ++j )
		{
			EXPECT_EQ(i, ggBinarySearch((void**)arr, j, ggComp_int, (void*)arr[i]));
		}
	}
}
