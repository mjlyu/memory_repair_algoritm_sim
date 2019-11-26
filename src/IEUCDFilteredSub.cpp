#include "IEUCDFilteredSub.h"


bool IEUCDFilteredSub::repair_with_spare_col(uint32_t eCol)
{
	bool rslt = IEUCWFilteredSub::repair_with_spare_col(eCol);
	if (rslt)
	{
		isolated_EUCD_filter();
	}
	return rslt;
}

IEUCDFilteredSub::IEUCDFilteredSub(){}
IEUCDFilteredSub::~IEUCDFilteredSub(){}

IEUCDFilteredSub::IEUCDFilteredSub(const SubArray& sub):IEUCWFilteredSub(sub)
{
	isolated_EUCD_filter();
}

IEUCDFilteredSub::IEUCDFilteredSub(const IEUCDFilteredSub& sub):
	IEUCWFilteredSub(sub)
{}

IEUCDFilteredSub::IEUCDFilteredSub(const IEUCWFilteredSub& sub):IEUCWFilteredSub(sub)
{
	isolated_EUCD_filter();
}

void IEUCDFilteredSub::isolated_EUCD_filter()
{
	vector<EUCW>::iterator wit = EUCWs.begin();
	vector<ErrorNode>::iterator dit;
	uint32_t col;
	while(wit != EUCWs.end())
	{
		dit = wit->Errors.begin();
		uint32_t i = 0;
		while(dit != wit->Errors.end())
		{
			col = dit->col;
			if (colEUCDCnt[col] == 1)
			{
				vector<int> temp;
				for (uint32_t n = 0; n < wit->nErrs; n++)
				{
					if(n == i) continue;
					temp.push_back(n);
				}
				wit->PRDCombs.clear();
				wit->PRDCombs.push_back(temp);
				break;
			}
			dit++;
			i++;
		}
		wit++;
	}
}

