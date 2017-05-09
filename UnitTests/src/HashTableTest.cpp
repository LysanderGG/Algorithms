#include "gtest/gtest.h"
#include <HashTable.h>

class HashTableTest : public ::testing::Test 
{

public:
	struct keyValuePair {
		const char* key;
		const char* val;
	};

	HashTableTest()
	{
		ggResult eRes;

		eRes = ggHashTableInitialize(&m_strDic, ggHash_string, ggComp_str);
		EXPECT_EQ(GG_OK, eRes);
	}
	
	virtual ~HashTableTest()
	{
		ggHashTableFinalize(&m_strDic);
	}


	ggHashTable m_strDic;
};

TEST_F(HashTableTest, Initialize)
{
	ggResult eRes;
	ggHashTable dic;
	
	eRes = ggHashTableInitialize(&dic, ggHash_int, ggComp_int);
	EXPECT_EQ(GG_OK, eRes);

	ggHashTableFinalize(&dic);
}

TEST_F(HashTableTest, Finalize)
{
	ggResult eRes;
	ggHashTable dic;

	eRes = ggHashTableInitialize(&dic, ggHash_int, ggComp_int);
	ASSERT_EQ(GG_OK, eRes);

	eRes = ggHashTableAdd(&dic, (void*)1, (void*)123);
	ASSERT_EQ(GG_OK, eRes);

	ggHashTableFinalize(&dic);
}

TEST_F(HashTableTest, Add)
{
	ggResult eRes;

	eRes = ggHashTableAdd(&m_strDic, "first", "Hello");
	EXPECT_EQ(GG_OK, eRes);
	EXPECT_TRUE(ggHashTableExists(&m_strDic, "first"));
	EXPECT_FALSE(ggHashTableExists(&m_strDic, "second"));

	eRes = ggHashTableAdd(&m_strDic, "second", "World");
	EXPECT_EQ(GG_OK, eRes);
	EXPECT_TRUE(ggHashTableExists(&m_strDic, "first"));
	EXPECT_TRUE(ggHashTableExists(&m_strDic, "second"));

	const char* collisionStr[] = { "abo", "aev", "agi" };
	uint32_t nbCollisionStr = sizeof(collisionStr) / sizeof(*collisionStr);

	for( uint32_t i = 0; i < nbCollisionStr; ++i )
	{
		ASSERT_EQ(ggHash_string("first") % 53, ggHash_string((void*)collisionStr[i]) % 53);
		eRes = ggHashTableAdd(&m_strDic, (void*)collisionStr[i], "collision");
		EXPECT_EQ(GG_OK, eRes);
	}
	EXPECT_TRUE(ggHashTableExists(&m_strDic, "first"));
	EXPECT_TRUE(ggHashTableExists(&m_strDic, "second"));
	for( uint32_t i = 0; i < nbCollisionStr; ++i )
	{
		EXPECT_TRUE(ggHashTableExists(&m_strDic, (void*)collisionStr[i]));
	}
}

TEST_F(HashTableTest, Exists)
{
	ggResult eRes;

	eRes = ggHashTableAdd(&m_strDic, "first", "Hello");
	ASSERT_EQ(GG_OK, eRes);
	eRes = ggHashTableAdd(&m_strDic, "second", "World");
	ASSERT_EQ(GG_OK, eRes);

	EXPECT_TRUE(ggHashTableExists(&m_strDic, "first"));
	EXPECT_TRUE(ggHashTableExists(&m_strDic, "second"));
	EXPECT_FALSE(ggHashTableExists(&m_strDic, "third"));
	EXPECT_FALSE(ggHashTableExists(&m_strDic, "Second"));
}


TEST_F(HashTableTest, Get)
{
	ggResult eRes;
	keyValuePair pairs[] = {
		{ "first", "Hello" },
		{ "second", "World" },
		{ "abo", "collision1" },  // collision with first
		{ "aev", "collision2" }, // collision with first
		{ "agi", "collision3" }, // collision with first 
	};
	uint32_t nbPairs = sizeof(pairs) / sizeof(*pairs);
	for( uint32_t i = 0; i < nbPairs; ++i )
	{
		// Ugly hardcode
		if( i != 1 ) {
			ASSERT_EQ(ggHash_string("first") % 53, ggHash_string((void*)pairs[i].key) % 53);
		}

		eRes = ggHashTableAdd(&m_strDic, (void*)pairs[i].key, (void*)pairs[i].val);
		EXPECT_EQ(GG_OK, eRes);
	}

	const char* resultStr = NULL;
	for( uint32_t i = 0; i < nbPairs; ++i )
	{
		resultStr = NULL;
		eRes = ggHashTableGet(&m_strDic, (void*)pairs[i].key, (void**)&resultStr);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_STREQ(resultStr, pairs[i].val);
	}

	resultStr = NULL;
	eRes = ggHashTableGet(&m_strDic, (void*)"do not exist", (void**)&resultStr);
	EXPECT_EQ(GG_KEY_ERROR, eRes);
}

TEST_F(HashTableTest, Remove)
{
	ggResult eRes;
	keyValuePair pairs[] = {
		{ "first", "Hello" },
		{ "second", "World" },
		{ "abo", "collision1" },  // collision with first
		{ "aev", "collision2" }, // collision with first
		{ "agi", "collision3" }, // collision with first 
	};
	uint32_t nbPairs = sizeof(pairs) / sizeof(*pairs);
	for( uint32_t i = 0; i < nbPairs; ++i )
	{
		eRes = ggHashTableAdd(&m_strDic, (void*)pairs[i].key, (void*)pairs[i].val);
		EXPECT_EQ(GG_OK, eRes);
	}

	const char* resultStr = NULL;
	for( uint32_t i = 0; i < nbPairs; ++i )
	{
		resultStr = NULL;
		eRes = ggHashTableGet(&m_strDic, (void*)pairs[i].key, (void**)&resultStr);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_STREQ(resultStr, pairs[i].val);
	}

	eRes = ggHashTableRemove(&m_strDic, (void*)"first");
	EXPECT_EQ(GG_OK, eRes);
	for( uint32_t i = 1; i < nbPairs; ++i )
	{
		resultStr = NULL;
		eRes = ggHashTableGet(&m_strDic, (void*)pairs[i].key, (void**)&resultStr);
		EXPECT_EQ(GG_OK, eRes);
		EXPECT_STREQ(resultStr, pairs[i].val);
	}

	eRes = ggHashTableRemove(&m_strDic, (void*)"first");
	EXPECT_EQ(GG_KEY_ERROR, eRes); // already removed

	eRes = ggHashTableAdd(&m_strDic, (void*)"first", (void*)"new");
	EXPECT_EQ(GG_OK, eRes);
	eRes = ggHashTableGet(&m_strDic, (void*)"first", (void**)&resultStr);
	EXPECT_EQ(GG_OK, eRes);
	EXPECT_STREQ(resultStr, "new");

	eRes = ggHashTableRemove(&m_strDic, (void*)"abo");
	EXPECT_EQ(GG_OK, eRes);
	eRes = ggHashTableRemove(&m_strDic, (void*)"aev");
	EXPECT_EQ(GG_OK, eRes);

	eRes = ggHashTableGet(&m_strDic, (void*)"agi", (void**)&resultStr);
	EXPECT_EQ(GG_OK, eRes);
	EXPECT_STREQ(resultStr, "collision3");
}
