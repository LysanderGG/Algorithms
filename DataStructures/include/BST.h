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
uint32_t		ggBSTGetNodeCount	(const ggBST* _this);
void			ggBSTPrintValues	(const ggBST* _this, void(*printFunc)(int32_t key, void* data));
ggResult		ggBSTFind			(const ggBST* _this, int32_t key, void** data);
/* Return 1 if in tree, 0 otherwise. */
int32_t			ggBSTIsInTree		(const ggBST* _this, int32_t key);
uint32_t		ggBSTGetHeight		(const ggBST* _this);
/* Return INT32_MAX if there is no node in the tree. */
int32_t			ggBSTGetMin			(const ggBST* _this);
/* Return INT32_MIN if there is no node in the tree. */
int32_t			ggBSTGetMax			(const ggBST* _this);
/* Does not really make sense but could be adapted to check for an arbitrary BinaryTree. 
 * Return 1 if is BST, 0 otherwise. */
int32_t			ggBSTIsBST			(const ggBST* _this);

void			ggBSTDelete			(const ggBST* _this, int32_t key);

#ifdef __cplusplus
}
#endif
