#ifndef _BSTNODE_H_
#define _BSTNODE_H_
#include "EUCDSub.h"
#include "IEUCWFilteredESub.h"
#include "IEUCDFilteredSub.h"

class BSTNode
{
	public:
		BSTNode();
		BSTNode(const SubArray&);
		BSTNode(const BSTNode&);
		~BSTNode();

		bool isRepaired();


	public:
		BSTNode* left;
		BSTNode* right;
		SubArray sub;


		

};

#endif
