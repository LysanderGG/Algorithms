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
	// add test for height
}


