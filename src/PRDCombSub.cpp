
#include <vector>
#include "PRDCombSub.h"
#include "Descarte.h"
#include "common.h"

PRDCombSub::PRDCombSub(const EUCDSub& sub)
{
	initial();
	this->EUCWs = sub.EUCWs;
	this->EUCDs = sub.EUCDs;
	this->repairedRows = sub.repairedRows;
	this->repairedCols = sub.repairedCols;
	this->nAvaSpRows = sub.nAvaSpRows;
	this->nAvaSpCols = sub.nAvaSpCols;
	construct_PRDCombs();
}

PRDCombSub::PRDCombSub(const IEUCWFilteredSub& sub):IEUCWFilteredSub(sub)
{
	PRDCombs.clear();
	construct_PRDCombs();
}

PRDCombSub::PRDCombSub(const IEUCDFilteredSub& sub):IEUCWFilteredSub(sub)
{
	PRDCombs.clear();
	construct_PRDCombs();
}


void PRDCombSub::create_PRDSub(SubArray& arr, uint32_t sel)
{
	vector<ErrorNode> PRDBitMap;
	create_PRDBitMap(PRDBitMap, sel);
	create_PRDSub(arr, PRDBitMap);
}
size_t PRDCombSub::total_PRDCombs(){return PRDCombs.size();}

void PRDCombSub::create_PRDSub(SubArray& arr, vector<ErrorNode>& PRDBitMap)
{
	arr.initial();
	arr.errBitMap = PRDBitMap;
	arr.nAvaSpCols = nAvaSpCols;
	arr.nAvaSpRows = nAvaSpRows;
	arr.repairedRows = repairedRows;
	arr.repairedCols = repairedCols;
}
//private functions
void PRDCombSub::create_PRDBitMap(vector<ErrorNode>& PRDBitMap, uint32_t sel)
{
	if(sel >= PRDCombs.size())
	{
		ERROR("==sel out of range" << sel);
		exit(0);
	}
	PRDBitMap.clear();
	vector<uint32_t> combs = PRDCombs[sel];
	uint32_t local;
	uint32_t errNum;
	uint32_t row;
	uint32_t col;
	for(size_t i = 0; i < combs.size(); ++i)
	{
		local = combs[i];
		vector<int> localSelection = EUCWs[i].PRDCombs[local];
		for (size_t j = 0; j < localSelection.size();++j)
		{
			errNum = localSelection[j];
			row = EUCWs[i].Errors[errNum].row;
			col = EUCWs[i].Errors[errNum].col;
			PRDBitMap.push_back(ErrorNode(row,col));
		}
	}
}

void PRDCombSub::construct_PRDCombs()
{
	vector<uint32_t> nCombsPerEUCW;
	vector<EUCW>::iterator it = EUCWs.begin();
	while(it != EUCWs.end())
	{
		nCombsPerEUCW.push_back(it->PRDCombs.size());
		it++;
	}

	descarte(nCombsPerEUCW, PRDCombs);
}

void PRDCombSub::initial()
{
	IEUCWFilteredSub::initial();
	PRDCombs.clear();
}

PRDCombSub::PRDCombSub(){}
PRDCombSub::~PRDCombSub(){}
