#include "gtest/gtest.h"
#include <BST.h>

class BSTTest : public ::testing::Test 
{

public:
	BSTTest() 
	{
		ggBSTInitialize(&m_bst);
	}
	
	virtual ~BSTTest()
	{
		ggBSTFinalize(&m_bst);
	}

	ggBST m_bst;
};
TEST_F(BSTTest, InitializeFinalize)
{
	ggBST bst;
	
	ggBSTInitialize(&bst);
	ggBSTFinalize(&bst);
}

TEST_F(BSTTest, Insert)
{
	ggResult eRes;

	int32_t values[] = { 5, 2, 1, 4, 7 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggBSTInsert(&m_bst, values[i], (void*)values[i]);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_EQ(i+1, ggBSTGetNodeCount(&m_bst));
	}
}

TEST_F(BSTTest, GetNodeCount)
{
	ggResult eRes;

	int32_t values[] = { 5, 2, 1, 4, 7 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggBSTInsert(&m_bst, values[i], (void*)values[i]);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_EQ(i + 1, ggBSTGetNodeCount(&m_bst));
	}

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggBSTDelete(&m_bst, values[i]);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_EQ(nbValues - i - 1, ggBSTGetNodeCount(&m_bst));
	}

}

TEST_F(BSTTest, Find)
{
	ggResult eRes;

	int32_t values[] = { 5, 2, 1, 4, 7 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);
	int32_t data = 0;

	eRes = ggBSTFind(&m_bst, 5, (void**)&data);
	EXPECT_EQ(GG_KEY_ERROR, eRes);

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggBSTInsert(&m_bst, values[i], (void*)(values[i] + 17));
		EXPECT_EQ(GG_OK, eRes);

		eRes = ggBSTFind(&m_bst, values[i], (void**)&data);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_EQ(values[i] + 17, data);
	}

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggBSTFind(&m_bst, values[i], (void**)&data);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_EQ(values[i] + 17, data);
	}

	eRes = ggBSTFind(&m_bst, 48, (void**)&data);
	EXPECT_EQ(GG_KEY_ERROR, eRes);
	eRes = ggBSTFind(&m_bst, 0, (void**)&data);
	EXPECT_EQ(GG_KEY_ERROR, eRes);
	eRes = ggBSTFind(&m_bst, 6, (void**)&data);
	EXPECT_EQ(GG_KEY_ERROR, eRes);
}

TEST_F(BSTTest, IsInTree)
{
	ggResult eRes;

	int32_t values[] = { 5, 2, 1, 4, 7 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	EXPECT_FALSE(ggBSTIsInTree(&m_bst, 5));

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggBSTInsert(&m_bst, values[i], (void*)values[i]);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_TRUE(ggBSTIsInTree(&m_bst, values[i]));
	}

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		EXPECT_TRUE(ggBSTIsInTree(&m_bst, values[i]));
	}

	EXPECT_FALSE(ggBSTIsInTree(&m_bst, 48));
	EXPECT_FALSE(ggBSTIsInTree(&m_bst, 0));
	EXPECT_FALSE(ggBSTIsInTree(&m_bst, 6));
}

TEST_F(BSTTest, GetHeight)
{
	ggResult eRes;

	int32_t values[] = { 5, 2, 1, 4, 7 };
	int32_t height[] = { 1, 2, 3, 3, 3 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	EXPECT_EQ(0, ggBSTGetHeight(&m_bst));

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggBSTInsert(&m_bst, values[i], (void*)values[i]);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_EQ(height[i], ggBSTGetHeight(&m_bst));
	}
}

TEST_F(BSTTest, GetMin)
{
	ggResult eRes;

	int32_t values[] = { 5, 2, 1, 4, 7 };
	int32_t min[]	 = { 5, 2, 1, 1, 1 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	EXPECT_EQ(INT32_MAX, ggBSTGetMin(&m_bst));

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggBSTInsert(&m_bst, values[i], (void*)values[i]);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_EQ(min[i], ggBSTGetMin(&m_bst));
	}
}

TEST_F(BSTTest, GetMax)
{
	ggResult eRes;

	int32_t values[] = { 5, 2, 1, 4, 7 };
	int32_t max[]    = { 5, 5, 5, 5, 7 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	EXPECT_EQ(INT32_MIN, ggBSTGetMax(&m_bst));

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggBSTInsert(&m_bst, values[i], (void*)values[i]);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_EQ(max[i], ggBSTGetMax(&m_bst));
	}
}

TEST_F(BSTTest, IsBST)
{
	ggResult eRes;

	int32_t values[] = { 5, 2, 1, 4, 7 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	EXPECT_TRUE(ggBSTIsBST(&m_bst));

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggBSTInsert(&m_bst, values[i], (void*)values[i]);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_TRUE(ggBSTIsBST(&m_bst));
	}
}

TEST_F(BSTTest, Delete)
{
	ggResult eRes;
	int32_t values[] = { 5, 2, 1, 4, 7 };
	uint32_t nbValues = sizeof(values) / sizeof(*values);

	EXPECT_EQ(GG_KEY_ERROR, ggBSTDelete(&m_bst, 1));

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggBSTInsert(&m_bst, values[i], (void*)values[i]);
		EXPECT_EQ(GG_OK, eRes);
	}

	for( uint32_t i = 0; i < nbValues; ++i )
	{
		eRes = ggBSTDelete(&m_bst, values[i]);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_TRUE(ggBSTIsBST(&m_bst));
	}
}
