#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "gtest/gtest.h"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1274);

	int res = RUN_ALL_TESTS();

	getchar();

	return res;
}