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
	if( !node ) {
		return newNode;
	}

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



/* ------------------------------------------------------------------------- */
