#include "gtest/gtest.h"
#include "List.h"

class ListTest : public ::testing::Test 
{

public:
	ListTest() 
	{
		ggListInitialize(&m_list);
	}
	
	virtual ~ListTest()
	{
		ggListFinalize(&m_list);
	}


	ggList m_list;
};

TEST_F(ListTest, Initialize)
{
	ggList list;
	
	ggListInitialize(&list);
	EXPECT_EQ(0U, ggListGetSize(&list));
	EXPECT_EQ(NULL, ggListFront(&list));

	ggListFinalize(&list);
}

TEST_F(ListTest, Finalize)
{
	ggResult eRes;
	ggList list;

	ggListInitialize(&list);

	eRes = ggListPushFront(&list, (void*)123);
	ASSERT_EQ(GG_OK, eRes);
	ASSERT_EQ(1U, ggListGetSize(&list));

	ggListFinalize(&list);
	EXPECT_EQ(0U, ggListGetSize(&list));
	EXPECT_EQ(NULL, ggListFront(&list));
}

TEST_F(ListTest, GetSize)
{
	ggResult eRes;

	EXPECT_EQ(0U, ggListGetSize(&m_list));

	eRes = ggListPushFront(&m_list, (void*)123);
	ASSERT_EQ(GG_OK, eRes);
	EXPECT_EQ(1U, ggListGetSize(&m_list));

	eRes = ggListPushFront(&m_list, (void*)234);
	ASSERT_EQ(GG_OK, eRes);
	EXPECT_EQ(2U, ggListGetSize(&m_list));
}

TEST_F(ListTest, IsEmpty)
{
	ggResult eRes;

	EXPECT_TRUE(ggListIsEmpty(&m_list));

	eRes = ggListPushFront(&m_list, (void*)123);
	ASSERT_EQ(GG_OK, eRes);
	EXPECT_FALSE(ggListIsEmpty(&m_list));
}

TEST_F(ListTest, GetValueAt)
{
	ggResult eRes;

	int32_t values[] = { 123, 234, 345, 9 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggListPushBack(&m_list, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		int32_t value = (int32_t)ggListGetValueAt(&m_list, i);
		EXPECT_EQ(values[i], value);
	}
}

TEST_F(ListTest, PushFront)
{
	ggResult eRes;

	int32_t values[] = { 123, 234, 345, 9 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggListPushFront(&m_list, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		int32_t value = (int32_t)ggListGetValueAt(&m_list, i);
		EXPECT_EQ(values[nbValues - i - 1], value);
	}
}

TEST_F(ListTest, PopFront)
{
	ggResult eRes;

	int32_t values[] = { 123, 234, 345, 9 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggListPushFront(&m_list, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		int32_t value = (int32_t)ggListPopFront(&m_list);
		EXPECT_EQ(values[nbValues - i - 1], value);
	}
}

TEST_F(ListTest, PushBack)
{
	ggResult eRes;

	int32_t values[] = { 123, 234, 345, 9 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggListPushBack(&m_list, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		int32_t value = (int32_t)ggListGetValueAt(&m_list, i);
		EXPECT_EQ(values[i], value);
	}
}


TEST_F(ListTest, PopBack)
{
	ggResult eRes;

	int32_t values[] = { 123, 234, 345, 9 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggListPushBack(&m_list, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		int32_t value = (int32_t)ggListPopBack(&m_list);
		EXPECT_EQ(values[nbValues - i - 1], value);
	}
}

TEST_F(ListTest, Front)
{
	ggResult eRes;
	int32_t value;

	value = (int32_t)ggListFront(&m_list);
	EXPECT_EQ(0, value); // ggListFront returns NULL as there are no items.

	eRes = ggListPushBack(&m_list, (void*)42);
	ASSERT_EQ(GG_OK, eRes);
	value = (int32_t)ggListFront(&m_list);
	EXPECT_EQ(42, value);

	eRes = ggListPushBack(&m_list, (void*)123);
	ASSERT_EQ(GG_OK, eRes);
	value = (int32_t)ggListFront(&m_list);
	EXPECT_EQ(42, value);

	eRes = ggListPushFront(&m_list, (void*)456);
	ASSERT_EQ(GG_OK, eRes);
	value = (int32_t)ggListFront(&m_list);
	EXPECT_EQ(456, value);
}

TEST_F(ListTest, Back)
{
	ggResult eRes;
	int32_t value;

	value = (int32_t)ggListBack(&m_list);
	EXPECT_EQ(0, value); // ggListFront returns NULL as there are no items.

	eRes = ggListPushBack(&m_list, (void*)42);
	ASSERT_EQ(GG_OK, eRes);
	value = (int32_t)ggListBack(&m_list);
	EXPECT_EQ(42, value);

	eRes = ggListPushBack(&m_list, (void*)123);
	ASSERT_EQ(GG_OK, eRes);
	value = (int32_t)ggListBack(&m_list);
	EXPECT_EQ(123, value);

	eRes = ggListPushFront(&m_list, (void*)456);
	ASSERT_EQ(GG_OK, eRes);
	value = (int32_t)ggListBack(&m_list);
	EXPECT_EQ(123, value);
}

TEST_F(ListTest, Insert)
{
	ggResult eRes;
	int32_t value;

	eRes = ggListInsert(&m_list, 0, (void*)123);
	ASSERT_EQ(GG_OK, eRes);
	eRes = ggListInsert(&m_list, 1, (void*)456);
	ASSERT_EQ(GG_OK, eRes);
	eRes = ggListInsert(&m_list, 0, (void*)42);
	ASSERT_EQ(GG_OK, eRes);

	value = (int32_t)ggListPopFront(&m_list);
	EXPECT_EQ(42, value);
	value = (int32_t)ggListPopFront(&m_list);
	EXPECT_EQ(123, value);
	value = (int32_t)ggListPopFront(&m_list);
	EXPECT_EQ(456, value);
}

TEST_F(ListTest, Erase)
{
	ggResult eRes;

	int32_t values[] = { 123, 234, 345, 9 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggListPushBack(&m_list, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	ggListErase(&m_list, 1);
	EXPECT_EQ(123, (int32_t)ggListGetValueAt(&m_list, 0));
	EXPECT_EQ(345, (int32_t)ggListGetValueAt(&m_list, 1));
	EXPECT_EQ(  9, (int32_t)ggListGetValueAt(&m_list, 2));
	EXPECT_EQ(  0, (int32_t)ggListGetValueAt(&m_list, 3)); // NULL

	ggListErase(&m_list, 2);
	EXPECT_EQ(123, (int32_t)ggListGetValueAt(&m_list, 0));
	EXPECT_EQ(345, (int32_t)ggListGetValueAt(&m_list, 1));
	EXPECT_EQ(  0, (int32_t)ggListGetValueAt(&m_list, 2)); // NULL
}

TEST_F(ListTest, GetValueAtFromEnd)
{
	ggResult eRes;

	int32_t values[] = { 123, 234, 345, 9 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggListPushBack(&m_list, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	EXPECT_EQ(  9, (int32_t)ggListGetValueAtFromEnd(&m_list, 0));
	EXPECT_EQ(345, (int32_t)ggListGetValueAtFromEnd(&m_list, 1));
	EXPECT_EQ(234, (int32_t)ggListGetValueAtFromEnd(&m_list, 2));
	EXPECT_EQ(123, (int32_t)ggListGetValueAtFromEnd(&m_list, 3));
}

TEST_F(ListTest, Reverse)
{
	ggResult eRes;

	int32_t values[] = { 123, 234, 345, 9 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggListPushBack(&m_list, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	ggListReverse(&m_list);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		int32_t value = (int32_t)ggListPopFront(&m_list);
		EXPECT_EQ(values[nbValues - i - 1], value);
	}
}

TEST_F(ListTest, Remove)
{
	ggResult eRes;

	int32_t values[] = { 1, 9, 9, 2, 3, 9 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggListPushBack(&m_list, (void*)values[i]);
		ASSERT_EQ(GG_OK, eRes);
	}

	ggListRemove(&m_list, (void*)9);
	EXPECT_EQ(1, (int32_t)ggListGetValueAt(&m_list, 0));
	EXPECT_EQ(9, (int32_t)ggListGetValueAt(&m_list, 1));
	EXPECT_EQ(2, (int32_t)ggListGetValueAt(&m_list, 2));

	ggListRemove(&m_list, (void*)9);
	EXPECT_EQ(1, (int32_t)ggListGetValueAt(&m_list, 0));
	EXPECT_EQ(2, (int32_t)ggListGetValueAt(&m_list, 1));
	EXPECT_EQ(3, (int32_t)ggListGetValueAt(&m_list, 2));

	ggListRemove(&m_list, (void*)1);
	EXPECT_EQ(2, (int32_t)ggListGetValueAt(&m_list, 0));
	EXPECT_EQ(3, (int32_t)ggListGetValueAt(&m_list, 1));
	EXPECT_EQ(9, (int32_t)ggListGetValueAt(&m_list, 2));

	ggListRemove(&m_list, (void*)9);
	EXPECT_EQ(2, (int32_t)ggListGetValueAt(&m_list, 0));
	EXPECT_EQ(3, (int32_t)ggListGetValueAt(&m_list, 1));
	EXPECT_EQ(0, (int32_t)ggListGetValueAt(&m_list, 2)); // NULL
}
