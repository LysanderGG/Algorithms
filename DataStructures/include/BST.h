#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <gg.h>

typedef struct ggBSTNode ggBSTNode;

struct ggBSTNode {
	int32_t		key;
	void*		data;
	ggBSTNode*	leftChild;
	ggBSTNode*	rightChild;
};

struct ggBST {
	ggBSTNode* root;
};

void			ggBSTInitialize		(ggBST* _this);
void			ggBSTFinalize		(ggBST* _this);

ggResult		ggBSTInsert			(ggBST* _this, int32_t key, void* data);

#ifdef __cplusplus
}
#endif
