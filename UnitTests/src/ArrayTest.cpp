#include "gtest/gtest.h"
#include "Array.h"

class ArrayTest : public ::testing::Test 
{

public:
	ArrayTest() 
	{
		ggResult eRes;

		eRes = ggPointerArrayInitialize(&m_array, 0);
		EXPECT_EQ(GG_OK, eRes);
	}
	
	virtual ~ArrayTest()
	{
		ggPointerArrayFinalize(&m_array);
	}


	ggPointerArray m_array;
};

TEST_F(ArrayTest, Initialize)
{
	ggResult eRes;
	ggPointerArray arr;
	
	eRes = ggPointerArrayInitialize(&arr, 0);
	EXPECT_EQ(GG_OK, eRes);
	EXPECT_EQ(16U, ggPointerArrayGetCapacity(&arr));
	EXPECT_EQ(0U, ggPointerArrayGetSize(&arr));

	ggPointerArrayFinalize(&arr);

	eRes = ggPointerArrayInitialize(&arr, 7);
	EXPECT_EQ(GG_OK, eRes);
	EXPECT_EQ(7U, ggPointerArrayGetCapacity(&arr));
	EXPECT_EQ(0U, ggPointerArrayGetSize(&arr));

	ggPointerArrayFinalize(&arr);
}

TEST_F(ArrayTest, Finalize)
{
	ggResult eRes;
	ggPointerArray arr;

	eRes = ggPointerArrayInitialize(&arr, 0);
	EXPECT_EQ(GG_OK, eRes);
	eRes = ggPointerArrayInsert(&arr, 0, (void*)12345678);
	EXPECT_EQ(GG_OK, eRes);
	EXPECT_EQ(16U, ggPointerArrayGetCapacity(&arr));
	EXPECT_EQ(1U, ggPointerArrayGetSize(&arr));

	ggPointerArrayFinalize(&arr);
	EXPECT_EQ(0U, ggPointerArrayGetCapacity(&arr));
	EXPECT_EQ(0U, ggPointerArrayGetSize(&arr));
}

TEST_F(ArrayTest, GetCapacity)
{
	ggResult eRes;
	uint32_t capacity;

	capacity = ggPointerArrayGetCapacity(&m_array);
	EXPECT_EQ(16U, capacity);

	for( uint32_t i = 0; i < 17; ++i )
	{
		eRes = ggPointerArrayPush(&m_array, (void*)i);
		ASSERT_EQ(GG_OK, eRes);
	}

	capacity = ggPointerArrayGetCapacity(&m_array);
	EXPECT_EQ(32U, capacity);

	for( uint32_t i = 0; i < 10; ++i )
	{
		ggPointerArrayPop(&m_array);
	}

	capacity = ggPointerArrayGetCapacity(&m_array);
	EXPECT_EQ(16U, capacity);

	for( uint32_t i = 0; i < 10; ++i )
	{
		ggPointerArrayPop(&m_array);
	}

	capacity = ggPointerArrayGetCapacity(&m_array);
	EXPECT_EQ(2U, capacity);
}

TEST_F(ArrayTest, GetSize)
{
	ggResult eRes;
	uint32_t size;

	size = ggPointerArrayGetSize(&m_array);
	EXPECT_EQ(0U, size);

	for( uint32_t i = 0; i < 17; ++i )
	{
		eRes = ggPointerArrayPush(&m_array, (void*)i);
		ASSERT_EQ(GG_OK, eRes);
		size = ggPointerArrayGetSize(&m_array);
		EXPECT_EQ(i + 1, size);
	}
}

TEST_F(ArrayTest, IsEmpty)
{
	ggResult eRes;
	uint32_t isEmpty;

	isEmpty = ggPointerArrayIsEmpty(&m_array);
	EXPECT_EQ(0U, isEmpty);

	eRes = ggPointerArrayPush(&m_array, (void*)123);
	ASSERT_EQ(GG_OK, eRes);
	isEmpty = ggPointerArrayIsEmpty(&m_array);
	EXPECT_TRUE(isEmpty);
}

TEST_F(ArrayTest, GetItem)
{
	ggResult eRes;
	void* item;

	item = ggPointerArrayGetItem(&m_array, 0);
	EXPECT_EQ(NULL, item);

	eRes = ggPointerArrayPush(&m_array, (void*)123);
	ASSERT_EQ(GG_OK, eRes);
	item = ggPointerArrayGetItem(&m_array, 0);
	EXPECT_EQ(123, (int32_t)item);
}

TEST_F(ArrayTest, Insert)
{
	ggResult eRes;
	void* item;

	item = ggPointerArrayGetItem(&m_array, 0);
	EXPECT_EQ(NULL, item);

	eRes = ggPointerArrayInsert(&m_array, 0, (void*)123);
	ASSERT_EQ(GG_OK, eRes);
	eRes = ggPointerArrayInsert(&m_array, 1, (void*)456);
	ASSERT_EQ(GG_OK, eRes);
	eRes = ggPointerArrayInsert(&m_array, 0, (void*)789);
	ASSERT_EQ(GG_OK, eRes);

	item = ggPointerArrayGetItem(&m_array, 0);
	EXPECT_EQ(789, (int32_t)item);
	item = ggPointerArrayGetItem(&m_array, 1);
	EXPECT_EQ(123, (int32_t)item);
	item = ggPointerArrayGetItem(&m_array, 2);
	EXPECT_EQ(456, (int32_t)item);

}

TEST_F(ArrayTest, Push)
{
	ggResult eRes;
	void* item;
	uint32_t values[] = { 123, 456, 789 };
	size_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggPointerArrayPush(&m_array, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}
	
	for( uint32_t i = 0; i < nbValues; ++i )
	{
		item = ggPointerArrayGetItem(&m_array, i);
		EXPECT_EQ(values[i], (uint32_t)item);
	}
}

TEST_F(ArrayTest, Prepend)
{
	ggResult eRes;
	void* item;
	uint32_t values[] = { 123, 456, 789 };
	size_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggPointerArrayPrepend(&m_array, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		item = ggPointerArrayGetItem(&m_array, i);
		EXPECT_EQ(values[nbValues-i-1], (uint32_t)item);
	}
}

TEST_F(ArrayTest, Pop)
{
	ggResult eRes;
	void* item;
	uint32_t values[] = { 123, 456, 789 };
	size_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggPointerArrayPush(&m_array, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	for( uint32_t i = nbValues; i > 0; --i )
	{
		item = ggPointerArrayPop(&m_array);
		EXPECT_EQ(values[i-1], (uint32_t)item);
	}
	EXPECT_EQ(0U, ggPointerArrayGetSize(&m_array));
}

TEST_F(ArrayTest, Delete)
{
	ggResult eRes;
	void* item;
	uint32_t values[] = { 123, 456, 789 };
	size_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggPointerArrayPush(&m_array, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	eRes = ggPointerArrayDelete(&m_array, 1);
	ASSERT_EQ(GG_OK, eRes);

	item = ggPointerArrayGetItem(&m_array, 0);
	EXPECT_EQ(123, (uint32_t)item);
	item = ggPointerArrayGetItem(&m_array, 1);
	EXPECT_EQ(789, (uint32_t)item);
	item = ggPointerArrayGetItem(&m_array, 2);
	EXPECT_EQ(NULL, item);
}

TEST_F(ArrayTest, Remove)
{
	ggResult eRes;
	uint32_t values[] = { 123, 456, 789 };
	size_t nbValues = sizeof(values) / sizeof(*values);
	int32_t idx;

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggPointerArrayPush(&m_array, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	idx = ggPointerArrayFind(&m_array, (void*)456);
	EXPECT_EQ(1, idx);

	eRes = ggPointerArrayRemove(&m_array, (void*)456);
	ASSERT_EQ(GG_OK, eRes);

	idx = ggPointerArrayFind(&m_array, (void*)456);
	EXPECT_EQ(-1, idx);
}

TEST_F(ArrayTest, Find)
{
	ggResult eRes;
	uint32_t values[] = { 123, 456, 789 };
	size_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggPointerArrayPush(&m_array, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		int32_t idx = ggPointerArrayFind(&m_array, (void*)values[i]);
		EXPECT_EQ(i, idx);
	}
}
