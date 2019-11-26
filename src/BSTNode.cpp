#include "BSTNode.h" 

bool BSTNode::isRepaired()
{
	return sub.total_error_num()==0;
}

BSTNode::	BSTNode():left(NULL),right(NULL)
{};

BSTNode::	BSTNode(const SubArray& arr):left(NULL), right(NULL),sub(arr)
{};

BSTNode::	BSTNode(const BSTNode& node):left(NULL), right(NULL),sub(node.sub)
{};

BSTNode::	~BSTNode(){};

