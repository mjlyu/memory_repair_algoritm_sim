#include <iostream>
#include <time.h>
#include "SubArray.h"
#include "IEUCDFilteredSub.h"
#include "BSTRepair.h"
#include "PRDCombSub.h"
#include "CombAndRepair.h"
#include "HeuristicRepair.h"
int main()
{
	SubArray sub(0);
	sub.error_inject(ErrorNode(6,273));
	sub.error_inject(ErrorNode(6,356));

	sub.error_inject(ErrorNode(20,521));
	sub.error_inject(ErrorNode(20,508));

	sub.error_inject(ErrorNode(21,177));
	sub.error_inject(ErrorNode(21,264));

	sub.error_inject(ErrorNode(63,40));
	sub.error_inject(ErrorNode(63,116));

	sub.error_inject(ErrorNode(96,15));
	sub.error_inject(ErrorNode(96,105));

	sub.error_inject(ErrorNode(107,126));
	sub.error_inject(ErrorNode(107,102));

	sub.error_inject(ErrorNode(129,496));
	sub.error_inject(ErrorNode(129,465));

	sub.error_inject(ErrorNode(294,301));
	sub.error_inject(ErrorNode(294,404));

	sub.error_inject(ErrorNode(303,271));
	sub.error_inject(ErrorNode(303,185));

	sub.error_inject(ErrorNode(362,474));
	sub.error_inject(ErrorNode(362,479));
	sub.error_inject(ErrorNode(362,486));

	sub.error_inject(ErrorNode(450,192));
	sub.error_inject(ErrorNode(450,185));

	sub.error_inject(ErrorNode(486,370));
	sub.error_inject(ErrorNode(486,389));
	sub.error_inject(ErrorNode(505,397));
	sub.error_inject(ErrorNode(505,393));


	sub.error_inject(ErrorNode(10,10));
	sub.error_inject(ErrorNode(11,11));
	sub.error_inject(ErrorNode(8,12));

	HeuristicRepair HSub(sub);

	EUCDSub ESub(sub);
	CombAndRepair CSub(ESub);
	CSub.BST_repair();

	//srand((unsigned int)time(NULL));
	//int nGoodH = 0;
	//int nGoodC = 0;
	//while(1)
	//{
	//	SubArray sub(260);
	//	HeuristicRepair HSub(sub);
	//	EUCDSub ESub(sub);
	//	CombAndRepair CSub(ESub);
	//	CSub.BST_repair();
	//	nGoodH += HSub.isRepaired();
	//	nGoodC += CSub.isRepaired();

	//	if (nGoodH > nGoodC)
	//	{
	//		cout << "Error" << endl;
	//		return 0;
	//	}
	//}




	////fault-driven bitmap, set SC=SR=4
	//sub.error_inject(ErrorNode(3,4));
	//sub.error_inject(ErrorNode(3,5));
	//sub.error_inject(ErrorNode(3,6));
	//sub.error_inject(ErrorNode(3,7));
	//sub.error_inject(ErrorNode(4,4));
	//sub.error_inject(ErrorNode(5,5));
	//sub.error_inject(ErrorNode(6,6));
	//sub.error_inject(ErrorNode(7,7));
	//sub.error_inject(ErrorNode(8,8));
	//sub.error_inject(ErrorNode(9,9));
	//sub.error_inject(ErrorNode(10,10));
	//sub.error_inject(ErrorNode(11,11));
	//sub.error_inject(ErrorNode(8,12));
	//sub.error_inject(ErrorNode(9,12));
	//sub.error_inject(ErrorNode(10,12));
	//sub.error_inject(ErrorNode(11,12));
	//sub.single_fault_filter();
	//BSTRepair bst(sub);


	//sub.error_inject(ErrorNode(3,7));
	//sub.error_inject(ErrorNode(3,3));

	//sub.error_inject(ErrorNode(4,3));
	//sub.error_inject(ErrorNode(4,7));
	//sub.error_inject(ErrorNode(4,72));
	//sub.error_inject(ErrorNode(4,75));

	//sub.error_inject(ErrorNode(7,72));
	//sub.error_inject(ErrorNode(7,3));

	//sub.error_inject(ErrorNode(8,7));
	//sub.error_inject(ErrorNode(8,75));
	//
	//sub.error_inject(ErrorNode(8,151));
	//sub.error_inject(ErrorNode(8,152));

	//sub.error_inject(ErrorNode(9,9));
	//sub.error_inject(ErrorNode(6,6));


	//sub.error_inject(ErrorNode(10,153));
	//sub.error_inject(ErrorNode(10,159));

	//sub.error_inject(ErrorNode(17,72));
	//sub.error_inject(ErrorNode(17,9));
	//sub.error_inject(ErrorNode(17,7));

	//sub.error_inject(ErrorNode(19,33));
	//sub.error_inject(ErrorNode(19,53));
	//sub.error_inject(ErrorNode(19,72));
	//sub.error_inject(ErrorNode(19,75));
	//sub.error_inject(ErrorNode(19,31));

	//sub.error_inject(ErrorNode(18,75));
	//sub.error_inject(ErrorNode(18,7));

	//
	//sub.error_inject(ErrorNode(22,19));
	//sub.error_inject(ErrorNode(22,39));

	//sub.error_inject(ErrorNode(28,20));
	//sub.error_inject(ErrorNode(28,50));
	//sub.error_inject(ErrorNode(28,59));
	//

	return 0;
}
