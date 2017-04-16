#include "gtest/gtest.h"
#include "Array.h"

class ArrayTest : public ::testing::Test 
{
	ArrayTest() 
	{
	}
	
	virtual ~ArrayTest()
	{
	}
};


TEST(ArrayTest, Create)
{
	ASSERT_EQ(1, 1);
}
