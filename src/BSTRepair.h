#ifndef _BSTREPAIR_H_
#define _BSTREPAIR_H_
#include "BSTNode.h"

class BSTRepair
{
	public:
		BSTRepair():bstRoot(NULL),repaired(false){};
		BSTRepair(const SubArray& sub);
		~BSTRepair();
		bool isRepaired();
	

	private:// functions			
		void repair_with_spare_row(BSTNode* node, uint32_t eRow);
		void repair_with_spare_col(BSTNode* node, uint32_t eCol);
		void bst_traveral(BSTNode* node);
		void destroy_bst(BSTNode* node);

	public:
		vector<BSTNode> solutions;

	private:
		BSTNode* bstRoot;
		bool repaired;



};


#endif
