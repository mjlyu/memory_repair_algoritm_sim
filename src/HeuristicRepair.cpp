#include "HeuristicRepair.h"


HeuristicRepair::HeuristicRepair(const SubArray& sub):EUCDSub(sub),isSucceed(false)
{
	update_PRDCnt();
	repair();
}

bool HeuristicRepair::isRepaired()
{
	return isSucceed;
}

void HeuristicRepair::repair()
{
	while(EUCWs.size() != 0) 
	{
		uint32_t eRow = index_maxVal(rowPRDCnt);
		uint32_t eCol = index_maxVal(colPRDCnt);
		bool rslt;
		//if (rowPRDCnt[eRow] >= colPRDCnt[eCol])
		if (rowPRDCnt[eRow] >= rowPRDCnt[eCol])
		{
			rslt = repair_with_spare_row(eRow);
			if(!rslt)
			{
				rslt = repair_with_spare_col(eCol);
			}
			if(!rslt)
			{
				return;
			}
		}
		else
		{
			rslt = repair_with_spare_col(eCol);
			if(!rslt)
			{
				rslt = repair_with_spare_row(eRow);
			}
			if(!rslt)
			{
				return;
			}
		}
		update_PRDCnt();
	}
	isSucceed = true;
	return;
}



bool HeuristicRepair::repair_with_spare_row(uint32_t eRow)
{
	bool rslt = EUCDSub::repair_with_spare_row(eRow);
	if(rslt)
		update_PRDCnt();

	return rslt;
}

bool HeuristicRepair::repair_with_spare_col(uint32_t eCol)
{
	bool rslt = EUCDSub::repair_with_spare_col(eCol);
	if(rslt)
		update_PRDCnt();

	return rslt;
}

void HeuristicRepair::update_PRDCnt()
{
	rowPRDCnt.clear();
	colPRDCnt.clear();
	vector<EUCW>::iterator wit = EUCWs.begin();
	vector<ErrorNode>::iterator dit;
	uint32_t row;
	uint32_t col;
	while(wit != EUCWs.end())
	{
		row = wit->Errors[0].row;
		rowPRDCnt[row] += wit->nErrs - ECCCap;
		dit = wit->Errors.begin();
		while(dit != wit->Errors.end())
		{
			col = dit->col;
			colPRDCnt[col]++;
			dit++;
		}
		wit++;
	}
}

void HeuristicRepair::initial()
{}

HeuristicRepair::~HeuristicRepair(){};
