#include "EUCDSub.h"
#include <map>

bool EUCDSub::repair_with_spare_row(uint32_t eRow)
{
	if(nAvaSpRows == 0) return false;
	repairedRows.push_back(eRow);
	nAvaSpRows--;
  delete_EUCDs_in_row(eRow);
	return true;
}

bool EUCDSub::repair_with_spare_col(uint32_t eCol)
{
	if(nAvaSpCols == 0) return false;
	repairedCols.push_back(eCol);
	nAvaSpCols--;
  delete_EUCDs_in_col(eCol);
	return true;
}

void EUCDSub::delete_EUCDs_in_col(uint32_t eCol)
{
	// update EUCWs
	vector<EUCW>::iterator wit = EUCWs.begin();
	while(wit != EUCWs.end())
	{
		vector<ErrorNode>::iterator it = wit->Errors.begin();
		while (it != wit->Errors.end())
		{
			if (it->col ==  eCol)
			{
				it = wit->Errors.erase(it);
				wit->nErrs--;
			}
			else it++;
		}
		if (wit->nErrs <= ECCCap)
		{
			wit = EUCWs.erase(wit);
		}
		else 
		{
			wit->update_PRDCombs();
			wit++;
		}
	}
	// update EUCDs
	update_EUCDs();
}

void EUCDSub::update_EUCDs()
{
	EUCDs.clear();
	vector<EUCW>::iterator wit = EUCWs.begin();
	vector<ErrorNode>::iterator dit; 
	uint32_t row;
	uint32_t col;
	while(wit != EUCWs.end())
	{
		dit = wit->Errors.begin();
		row = dit->row;
		while(dit != wit->Errors.end())
		{
			col = dit->col;
			EUCDs.push_back(ErrorNode(row, col));
			dit++;
		}
		wit++;
	}
}

void EUCDSub::delete_EUCDs_in_row(uint32_t eRow)
{
	vector<EUCW>::iterator wit = EUCWs.begin();
	while (wit != EUCWs.end())
	{
		if(wit->Errors[0].row == eRow)
		{
			wit = EUCWs.erase(wit);
		}
		else wit++;
	}
	update_EUCDs();
}

EUCDSub::EUCDSub(){}

EUCDSub::~EUCDSub(){}

EUCDSub::EUCDSub(const SubArray& sub)
{
	initial();
	repairedRows = sub.repairedRows;
	repairedCols = sub.repairedCols;
	nAvaSpRows = sub.nAvaSpRows;
	nAvaSpCols = sub.nAvaSpCols;
	identify_EUCWs_and_EUCDs(sub);
}

EUCDSub::EUCDSub(const EUCDSub& sub)
{
	EUCWs = sub.EUCWs;
	EUCDs = sub.EUCDs;
	repairedRows = sub.repairedRows;
	repairedCols = sub.repairedCols;
	nAvaSpRows = sub.nAvaSpRows;
	nAvaSpCols = sub.nAvaSpCols;
}

void EUCDSub::identify_EUCWs_and_EUCDs(const SubArray& sub)
{
	map<uint32_t, uint32_t>::const_iterator it = sub.codeWordErrCnt.begin();
	vector<ErrorNode> bitMap = sub.errBitMap;
	vector<ErrorNode>::iterator itt;
	while(it != sub.codeWordErrCnt.end())
	{
		if(it->second > ECCCap)
		{
			uint32_t nErrs = it->second;
			EUCW eucw(nErrs);
			uint32_t row=it->first / nCodeWordsPerRow;
			uint32_t nlocal = (it->first) % nCodeWordsPerRow;
			uint32_t lowBoundCol = nlocal * lenCodeWord;
			itt = bitMap.begin();
			while (itt != bitMap.end())
			{
				if (itt->row == row)
				{
					uint32_t col = itt->col;
					if ((col >= lowBoundCol) && (col < (lowBoundCol + lenCodeWord)))
					{
						eucw.Errors.push_back(ErrorNode(row, col));
						EUCDs.push_back(ErrorNode(row, col));
						itt = bitMap.erase(itt);
						itt--;
					}
				}
				itt++;
			}
			EUCWs.push_back(eucw);
		}
		it++;
	}
}

void EUCDSub::initial()
{
	EUCWs.clear();
	EUCDs.clear();
}
