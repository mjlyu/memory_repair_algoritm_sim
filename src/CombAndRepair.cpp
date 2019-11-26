#include "CombAndRepair.h"
#include "BSTRepair.h"

CombAndRepair::CombAndRepair(const EUCDSub& sub):PSub(sub),isSucceed(false)
{}

CombAndRepair::CombAndRepair(const IEUCWFilteredSub& sub):PSub(sub), isSucceed(false)
{}

CombAndRepair::CombAndRepair(const IEUCDFilteredSub& sub):PSub(sub), isSucceed(false)
{}

bool CombAndRepair::isRepaired(){ return isSucceed;}

void CombAndRepair::BST_repair()
{
	SubArray PRDSub;
	uint32_t nPRDCombs = PSub.total_PRDCombs();
	for(uint32_t sel = 0; sel < nPRDCombs; sel++)
	{
		PSub.create_PRDSub(PRDSub, sel);
		BSTRepair bst(PRDSub);
		if(!bst.isRepaired()) 
		{
			continue;
		}
		if (PSub.IEUCWs.size()==0)
		{
			isSucceed = true;
			return;
		}
		vector<BSTNode>::iterator it = bst.solutions.begin();
		while(it != bst.solutions.end())
		{
			IEUCWFilteredSub IWSub(it->sub);
			IWSub.IEUCWs = PSub.IEUCWs;
			if (IWSub.IEUCWs_repair())
			{
				isSucceed =  true;
				return;
			}
			it++;
		}
	}
}



