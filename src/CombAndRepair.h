#ifndef _COMBANDREPAIR_H_
#define _COMBANDREPAIR_H_
#include "PRDCombSub.h"
#include "BSTRepair.h"

class CombAndRepair
{
	public:
		CombAndRepair():isSucceed(false){};
		CombAndRepair(const EUCDSub&);
		CombAndRepair(const IEUCWFilteredSub&);
		CombAndRepair(const IEUCDFilteredSub&);
		~CombAndRepair(){};
		void BST_repair();
		bool isRepaired();

	private:
		PRDCombSub PSub;
		bool isSucceed;
};


#endif
