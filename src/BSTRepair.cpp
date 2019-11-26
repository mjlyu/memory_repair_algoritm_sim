#include "BSTRepair.h"
#include <queue>

bool BSTRepair::isRepaired()
{
	return repaired;
}
// construct BST with Breadth-first strategy until one repair solution is found
void BSTRepair::bst_traveral(BSTNode* mRoot) 
{
	if(mRoot == NULL) return;
	if(mRoot->isRepaired()) 
	{
		repaired = true;
		solutions.push_back(BSTNode(*mRoot));
		return;
	}
	if(mRoot->sub.isUnRepairalbe()) 
	{
		repaired = false;
		return;
	}
	if(mRoot->sub.sing_error_num() == 0)
	{
		mRoot->sub.single_faults_repair();
		repaired = true;
		solutions.push_back(BSTNode(*mRoot));
		return;
	}

	// start breadth-first traversal
	queue<BSTNode*> Que;
	Que.push(mRoot);
	while(!Que.empty())
	{
		// basic check
		BSTNode* node = Que.front(); 
		if(node->isRepaired())
		{
			repaired = true;
			solutions.push_back(BSTNode(*node));
			Que.pop();
			continue;
		}
		if (node->sub.isUnRepairalbe())
		{
			Que.pop();
			continue;
		}
		if (node->sub.sing_error_num() == 0)
		{
			node->sub.single_faults_repair();
			repaired = true;
			solutions.push_back(BSTNode(*node));
			Que.pop();
			continue;
		}
		// node expansion
		uint32_t eRow = node->sub.errBitMap[0].row;
		uint32_t eCol = node->sub.errBitMap[0].col;
		repair_with_spare_row(node, eRow);
		repair_with_spare_col(node, eCol);
		if(node->left != NULL)
		{
			Que.push(node->left);
		}
		if(node->right != NULL)
		{
			Que.push(node->right);
		}
		Que.pop();
	}
}

void BSTRepair::repair_with_spare_col(BSTNode* node, uint32_t eCol)
{
	if(node->isRepaired()) return;
	BSTNode* tmp = new BSTNode(*node);
	if (!tmp->sub.repair_with_spcol(eCol))
	{
		delete tmp;
		return;
	}
	if (tmp->sub.sing_error_num()==0)
	{
		if(!tmp->sub.isUnRepairalbe())
		{
			tmp->sub.single_faults_repair();
		}
		else
		{
			delete tmp;
			return;
		}
	}
	node->right = tmp;
}

void BSTRepair::repair_with_spare_row(BSTNode* node, uint32_t eRow)
{
	if(node->isRepaired()) return;
	BSTNode* tmp = new BSTNode(*node);
	if(!tmp->sub.repair_with_sprow(eRow))
	{
		delete tmp;
		return;
	}
	if (tmp->sub.sing_error_num()==0)
	{
		if(!tmp->sub.isUnRepairalbe())
		{
			tmp->sub.single_faults_repair();
		}
		else
		{
			delete tmp;
			return;
		}
	}
	node->left = tmp;
}

BSTRepair::BSTRepair(const SubArray& sub):bstRoot(NULL),repaired(false)
{
	solutions.clear();
	bstRoot = new BSTNode(sub);
	bst_traveral(bstRoot);
}

BSTRepair::~BSTRepair()
{
	destroy_bst(bstRoot);
}

void BSTRepair::destroy_bst(BSTNode* node)
{
	if(node == NULL) return;
	destroy_bst(node->left);
	destroy_bst(node->right);
	delete node;
}

