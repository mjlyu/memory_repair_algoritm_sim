
#include <algorithm>
#include <set>
#include "IEUCWFilteredESub.h" 
#include "CompHelper.h"
bool IEUCWFilteredSub::early_abort()
{
	// early abort according to the number ofisolated EUCWs
	if (IEUCWs.size() > nAvaSpCols + nAvaSpRows)
	{
		return true;
	}

	// early abort according to must-repair columns
	int nMustRepairCols = 0;
	int nMustRepairWords = 0;
	vector<EUCW>::const_iterator it = EUCWs.begin();
	vector<ErrorNode>::const_iterator dit;
	uint32_t col;
	set<uint32_t> mustRepairCols;
	while(it != EUCWs.end())
	{
		set<uint32_t> localMustRepairCols;
		dit = it->Errors.begin();
		while(dit != it->Errors.end())
		{
			col = dit->col;
			if (colEUCDCnt[col] > nAvaSpRows)
			{
				localMustRepairCols.insert(col);
			}
			dit++;
		}
		if (localMustRepairCols.size() > 1)
		{
			nMustRepairWords++;
			set<uint32_t>::iterator itt = localMustRepairCols.begin();
			while(itt!=localMustRepairCols.end())
			{
				mustRepairCols.insert(*itt++);
			}			
		}
		it++;
	}
	nMustRepairCols = mustRepairCols.size();
	if (nMustRepairCols - nMustRepairWords > (int)nAvaSpCols)
	{
		return true;
	}
	return false;
}


bool IEUCWFilteredSub::must_repair()
{
	// must repair EUCWs
	map<uint32_t, uint32_t>::iterator it = rowEUCDCnt.begin();
	while (it!=rowEUCDCnt.end())
	{
		uint32_t row = it->first;
		if(it->second - (ECCCap * rowEUCWCnt[row]) > nAvaSpCols)
		{
			if(nAvaSpRows > 0) 
			{
				repair_with_spare_row(row);
				it = rowEUCDCnt.begin();
			}
			else return false;
		}
		else it++;
	}
	
	// must_repair IEUCWs
	vector<EUCW>::iterator wit = IEUCWs.begin();
	while(wit != IEUCWs.end())
	{
		if (wit->nErrs - ECCCap > nAvaSpCols)
		{
			if (nAvaSpRows > 0)
			{
				uint32_t eRow = wit->Errors[0].row;
				repairedRows.push_back(eRow);
				nAvaSpRows--;
				wit = IEUCWs.erase(wit);
			}
			else return false;
			
		}
		else wit++;
	}
	update_EUCDsInIEUCWs();
	return true;
}


bool IEUCWFilteredSub::IEUCWs_repair()
{
	// early abort
	if (IEUCWs.size() > nAvaSpRows + nAvaSpCols) return false;
	sort(IEUCWs.begin(), IEUCWs.end(), CompGreater());

	// repair EUCWs with EUCDs more than ECCap+1, which can be repaired with one spare row 
	// or several spare columns 
	vector<EUCW>::iterator it = IEUCWs.begin();
	while(it != IEUCWs.end() && it->nErrs > (ECCCap+1))
	{
		if (nAvaSpRows > 0)
		{
			uint32_t row = it->Errors[0].row;
			repairedRows.push_back(row);
			nAvaSpRows--;
			it = IEUCWs.erase(it);
		}
		else if (nAvaSpCols >= (it->nErrs-ECCCap))
		{
			uint32_t col;
			for(size_t i = 1; i < it->Errors.size(); ++i)
			{
				col = it->Errors[i].col;
				repairedCols.push_back(col);
			}
			nAvaSpCols -= (it->nErrs - ECCCap);
			it = IEUCWs.erase(it);
		}
		else return false;
	}

	// repair EUCWs with only ECCCap+1 EUCDs, which can be repaired using either one spare row or one spare column
	if (IEUCWs.size() > nAvaSpCols+nAvaSpRows) return false;
	it = IEUCWs.begin();
	while (it != IEUCWs.end())
	{
		if (nAvaSpRows > 0)
		{
			uint32_t row = it->Errors[0].row;
			repairedRows.push_back(row);
			nAvaSpRows--;
			it = IEUCWs.erase(it);
		}
		else if (nAvaSpCols > 0)
		{
			uint32_t col = it->Errors[0].col;
			repairedCols.push_back(col);
			nAvaSpCols--;
			it = IEUCWs.erase(it);
		}
		else return false;
	}

	update_EUCDsInIEUCWs();

	return true;
}

bool IEUCWFilteredSub::repair_with_spare_row(uint32_t eRow)
{
	bool rslt = EUCDSub::repair_with_spare_row(eRow);
	if (rslt)
	{
		update_EUCDCnt();
		update_rowEUCWCnt();
	}
	return rslt;
}

bool IEUCWFilteredSub::repair_with_spare_col(uint32_t eCol)
{
	bool rslt =  EUCDSub::repair_with_spare_col(eCol);
	if (rslt)
	{
		update_EUCDCnt();
		update_rowEUCWCnt();
	}
	return rslt;
}

IEUCWFilteredSub::IEUCWFilteredSub()
{}

IEUCWFilteredSub::IEUCWFilteredSub(const IEUCWFilteredSub& sub):
	EUCDSub(sub)
{
	IEUCWs = sub.IEUCWs;
	EUCDsInIEUCWs = sub.EUCDsInIEUCWs;
	rowEUCDCnt = sub.rowEUCDCnt;
	colEUCDCnt = sub.colEUCDCnt;
	rowEUCWCnt = sub.rowEUCWCnt;
}

IEUCWFilteredSub::IEUCWFilteredSub(const SubArray& sub):
	EUCDSub(sub)
{
	//initial();
	update_EUCDCnt();
	update_rowEUCWCnt();
	isolated_EUCW_filter();
	update_EUCDCnt();
	update_rowEUCWCnt();
}

IEUCWFilteredSub::IEUCWFilteredSub(const EUCDSub& sub):
	EUCDSub(sub)
{
	//initial();
	update_EUCDCnt();
	update_rowEUCWCnt();
	isolated_EUCW_filter();
	update_EUCDCnt();
	update_rowEUCWCnt();
}
IEUCWFilteredSub::~IEUCWFilteredSub()
{}

void IEUCWFilteredSub::isolated_EUCW_filter()
{
	IEUCWs.clear();
	vector<EUCW>::iterator wit = EUCWs.begin();	
	while(wit != EUCWs.end())
	{
		uint32_t row = wit->Errors[0].row;
		if(wit->nErrs == rowEUCDCnt[row]) // row isolated?
		{
			bool isolatedFlag = true;
			vector<ErrorNode>::iterator dit = wit->Errors.begin();
			while(dit != wit->Errors.end())
			{
				uint32_t col = dit->col;
				if (colEUCDCnt[col] > 1)
				{
					isolatedFlag = false;
					break;
				}
				else dit++;
			}
			if (isolatedFlag)
			{
				IEUCWs.push_back(EUCW(*wit));
				wit = EUCWs.erase(wit);
			}
			else wit++;
		}
		else wit++;
	}

	update_EUCDs();
	update_EUCDsInIEUCWs();
}

void IEUCWFilteredSub::update_EUCDsInIEUCWs()
{
	EUCDsInIEUCWs.clear();
	vector<EUCW>::iterator wit = IEUCWs.begin();
	vector<ErrorNode>::iterator dit;
	uint32_t row;
	uint32_t col;
	while (wit != IEUCWs.end())
	{
		dit = wit->Errors.begin();
		row = dit->row;
		while (dit != wit->Errors.end())
		{
			col = dit->col;
			EUCDsInIEUCWs.push_back(ErrorNode(row, col));
			dit++;
		}
		wit++;
	}
}

void IEUCWFilteredSub::update_EUCDCnt()
{
	rowEUCDCnt.clear();
	colEUCDCnt.clear();
	vector<ErrorNode>::iterator it = EUCDs.begin();
	while(it != EUCDs.end())
	{
		rowEUCDCnt[it->row]++;
		colEUCDCnt[it->col]++;
		it++;
	}
}
void IEUCWFilteredSub::update_rowEUCWCnt()
{
	rowEUCWCnt.clear();
	vector<EUCW>::iterator it = EUCWs.begin();
	uint32_t row;
	while(it != EUCWs.end())
	{
		row = it->Errors[0].row;
		rowEUCWCnt[row]++;
		it++;
	}
}

void IEUCWFilteredSub::initial()
{
	EUCDSub::initial();
	IEUCWs.clear();
	EUCDsInIEUCWs.clear();
	rowEUCDCnt.clear();
	colEUCDCnt.clear();
	rowEUCWCnt.clear();
}

