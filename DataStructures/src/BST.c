#include <BST.h>
#include <gg.h>
#include <stdlib.h>

/* ------------------------------------------------------------------------- */

static ggResult
_ggBSTNodeCreate(int32_t key, void* data, ggBSTNode** node)
{
	ggAssert(node);

	ggBSTNode* newNode = malloc(sizeof(ggBSTNode));
	GG_CONDITION(!newNode, GG_OUT_OF_MEMORY);

	newNode->key = key;
	newNode->data = data;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	*node = newNode;
	return GG_OK;
}

/* ------------------------------------------------------------------------- */

void
ggBSTInitialize(ggBST* _this)
{
	ggAssert(_this);
	_this->root = NULL;
}

static void 
_ggBSTFinalizeNode(ggBSTNode* node)
{
	ggAssert(node);

	if( node->leftChild )
	{
		_ggBSTFinalizeNode(node->leftChild);
	}
	if( node->rightChild )
	{
		_ggBSTFinalizeNode(node->rightChild);
	}
	free(node);
}
void
ggBSTFinalize(ggBST* _this)
{
	if( _this->root )
	{
		_ggBSTFinalizeNode(_this->root);
	}
}

/* ------------------------------------------------------------------------- */

static ggBSTNode*
_ggBSTNodeInsert(ggBSTNode* node, ggBSTNode* newNode)
{
	ggAssert(newNode);
	if( !node ) { return newNode; }

	if( newNode->key < node->key )
	{
		node->leftChild = _ggBSTNodeInsert(node->leftChild, newNode);
	}
	else
	{
		node->rightChild = _ggBSTNodeInsert(node->rightChild, newNode);
	}
	return node;
}
ggResult 
ggBSTInsert(ggBST* _this, int32_t key, void* data)
{
	ggAssert(_this);
	ggBSTNode* newNode = NULL;
	ggResult eRes = _ggBSTNodeCreate(key, data, &newNode);
	GG_CONDITION(GG_OK != eRes, eRes);

	_this->root = _ggBSTNodeInsert(_this->root, newNode);
	return GG_OK;
}

static uint32_t
_ggBSTNodeGetCount(const ggBSTNode* node)
{
	if( !node ) { return 0; }
	return 1 + _ggBSTNodeGetCount(node->leftChild) + _ggBSTNodeGetCount(node->rightChild);
}
uint32_t
ggBSTGetNodeCount(const ggBST* _this)
{
	ggAssert(_this);
	return _ggBSTNodeGetCount(_this->root);
}

static void
_ggBSTNodePrintValues(const ggBSTNode* node, void(*printFunc)(int32_t key, void* data))
{
	ggAssert(printFunc);
	if( !node ) { return; }
	if( node->leftChild ) {
		_ggBSTNodePrintValues(node->leftChild, printFunc);
	}
	printFunc(node->key, node->data);
	if( node->rightChild ) {
		_ggBSTNodePrintValues(node->rightChild, printFunc);
	}

}
void
ggBSTPrintValues(const ggBST* _this, void(*printFunc)(int32_t key, void* data))
{
	ggAssert(_this && printFunc);
	_ggBSTNodePrintValues(_this->root, printFunc);
}

static ggBSTNode*
_ggBSTNodeFindNode(ggBSTNode* node, int32_t key)
{
	if( !node ) { return NULL; }

	if( node->key == key )
	{
		return node;
	}
	else if( key < node->key )
	{
		return _ggBSTNodeFindNode(node->leftChild, key);
	}
	else
	{
		return _ggBSTNodeFindNode(node->rightChild, key);
	}
}
ggResult
ggBSTFind(const ggBST* _this, int32_t key, void** data)
{
	ggAssert(_this && data);

	ggBSTNode* node = _ggBSTNodeFindNode(_this->root, key);
	GG_CONDITION(!node, GG_KEY_ERROR);

	*data = node->data;
	return GG_OK;
}

int32_t
ggBSTIsInTree(const ggBST* _this, int32_t key)
{
	ggAssert(_this);
	return NULL != _ggBSTNodeFindNode(_this->root, key) ? 1 : 0;
}

static uint32_t
_ggBSTNodeGetHeight(const ggBSTNode* node)
{
	if( !node ) { return 0; }
	int32_t lh = _ggBSTNodeGetHeight(node->leftChild);
	int32_t rh = _ggBSTNodeGetHeight(node->rightChild);
	return 1 + max(lh, rh);
}
uint32_t
ggBSTGetHeight(const ggBST* _this)
{
	ggAssert(_this);
	return _ggBSTNodeGetHeight(_this->root);
}

int32_t
ggBSTGetMin(const ggBST* _this)
{
	ggAssert(_this);
	if( !_this->root ) { return INT32_MAX; }

	ggBSTNode* node = _this->root;
	while( node->leftChild ) {
		node = node->leftChild;
	}

	return node->key;
}

int32_t
ggBSTGetMax(const ggBST* _this)
{
	if( !_this->root ) { return INT32_MIN; }

	ggBSTNode* node = _this->root;
	while( node->rightChild ) {
		node = node->rightChild;
	}

	return node->key;
}

int32_t
_ggBSTNodeIsBST(const ggBSTNode* node, int32_t minKey, int32_t maxKey)
{
	if( !node ) { return 1; }
	if( node->key < minKey || node->key > maxKey ) { return 0; }
	return _ggBSTNodeIsBST(node->leftChild, minKey, node->key)
		&& _ggBSTNodeIsBST(node->rightChild, node->key, maxKey);
}
int32_t
ggBSTIsBST(const ggBST* _this)
{
	ggAssert(_this);
	return _ggBSTNodeIsBST(_this->root, INT32_MIN, INT32_MAX);
}


void
ggBSTDelete(const ggBST* _this, int32_t key)
{
	// TODO
}

/* ------------------------------------------------------------------------- */
