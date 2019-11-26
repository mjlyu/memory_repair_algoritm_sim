
#include "SubArray.h"

#include "parameters.h"
#include "common.h"
#include <iostream>
#include <algorithm>

// deconstructor
SubArray::~SubArray()
{}

// default constructor
SubArray::SubArray() :
nAvaSpRows(nSpRowsPerSub), nAvaSpCols(nSpColsPerSub)
{
  initial();
}
// constructor using error number
SubArray::SubArray(uint32_t nErrs) :
nAvaSpRows(nSpRowsPerSub), nAvaSpCols(nSpColsPerSub)
{
  initial();
  error_inject(nErrs);
}
// copy constructor
SubArray::SubArray(const SubArray& sa) 
{
  this->nAvaSpRows = sa.nAvaSpRows;
  this->nAvaSpCols = sa.nAvaSpCols;
  this->clstErrRow = sa.clstErrRow;
  this->clstErrCol = sa.clstErrCol;
  this->errBitMap = sa.errBitMap;
  this->rowErrCnt = sa.rowErrCnt;
  this->colErrCnt = sa.colErrCnt;
  this->codeWordErrCnt = sa.codeWordErrCnt;
	this->singleFault = sa.singleFault;
  this->repairedRows = sa.repairedRows;
  this->repairedCols = sa.repairedCols;
}
void SubArray::error_inject(uint32_t nErrs)
{
  for (uint32_t i = 0; i < nErrs; i++)
  {
    EType eType = error_type();
    uint32_t row = rand() % nRowsPerSub;
    uint32_t col = rand() % nColsPerSub;
    error_inject(row, col, eType);
  }
	update_errCnt();
	single_fault_filter();
	update_codeWordErrCnt();
}

void SubArray::error_inject(uint32_t row, uint32_t col, EType T)
{
	uint32_t eRow = row;
	uint32_t eCol = col;
	if (T == rowErr) {
		clstErrRow.insert(eRow);
		return;
	}
	if (T == colErr)
	{
		clstErrCol.insert(eCol);
		return;
	}
	if (T == sngErr)
	{
		if (errBitMap.size() != 0)
		{
			double flag = rand()%100/double(100);
			// row cluster effect
			if (flag < RowCoeff)
			{
				uint32_t indexRow = rand()%(errBitMap.size());
				eRow = errBitMap[indexRow].row;
			}
			// col cluster effect
			if(flag > 1-ColCoeff)
			{
				uint32_t indexCol = rand()%(errBitMap.size());
				eCol = errBitMap[indexCol].col;
			}
		}
		errBitMap.push_back(ErrorNode(eRow, eCol));
	}
}

void SubArray::error_inject(const ErrorNode& err)
{
	errBitMap.push_back(err);
	update_codeWordErrCnt();
	update_errCnt();
}

bool SubArray::repair_with_sprow(uint32_t eRow)
{
	if (nAvaSpRows == 0) return false;
	nAvaSpRows--;
	bitMap_delete_row(eRow);
	repairedRows.push_back(eRow);
	update_codeWordErrCnt();
	update_errCnt();
	return true;
}

bool SubArray::repair_with_spcol(uint32_t eCol)
{
	if (nAvaSpCols == 0) return false;
	nAvaSpCols--;
	bitMap_delete_col(eCol);
	repairedCols.push_back(eCol);
	update_codeWordErrCnt();
	update_errCnt();
	return true;
}

int SubArray::repair_row(uint32_t eRow)
{
	int repaired = bitMap_delete_row(eRow);
	//repairedRows.push_back(eRow);
	update_codeWordErrCnt();
	update_errCnt();
	return repaired;
}

int  SubArray::repair_col(uint32_t eCol)
{
	int repaired = bitMap_delete_col(eCol);
	//repairedCols.push_back(eCol);
	update_codeWordErrCnt();
	update_errCnt();
	return repaired;
}


bool SubArray::cluster_repair()
{
	if (clstErrRow.size() > nAvaSpRows) return false;
	if (clstErrCol.size() > nAvaSpCols) return false;
	set<int>::iterator it = clstErrRow.begin();
	while (it != clstErrRow.end())
	{
		repair_with_sprow(*it);
		it++;
	}
	it = clstErrCol.begin();
	while (it != clstErrCol.end())
	{
		repair_with_spcol(*it);
		it++;
	}
	clstErrRow.clear();
	clstErrCol.clear();
	return true;
}

bool SubArray::force_repair()
{
	if (errBitMap.size() == 0) return true;
	while (!rowErrCnt.empty())
	{
		uint32_t row = key_maxVal(rowErrCnt);
		if (rowErrCnt[row] <= nAvaSpCols) break;
		if (!repair_with_sprow(row)) return false;
	}
	while (!colErrCnt.empty())
	{
		uint32_t col = key_maxVal(colErrCnt);
		if (colErrCnt[col] <= nAvaSpRows) break;
		if (!repair_with_spcol(col)) return false;
	}
	return true;
}


// operator "=" redefinition
SubArray& SubArray::operator=(const SubArray& rhs)
{
	if (this != &rhs)
	{
		this->nAvaSpCols = rhs.nAvaSpCols;
		this->nAvaSpRows = rhs.nAvaSpRows;
		this->clstErrRow = rhs.clstErrRow;
		this->clstErrCol = rhs.clstErrCol;
		this->errBitMap = rhs.errBitMap;
		this->rowErrCnt = rhs.rowErrCnt;
		this->colErrCnt = rhs.colErrCnt;
		this->codeWordErrCnt = rhs.codeWordErrCnt;
		this->singleFault = rhs.singleFault;
		this->repairedRows = rhs.repairedRows;
		this->repairedCols = rhs.repairedCols;
	}
	return *this;
}

bool SubArray::repair()
{
	if (!cluster_repair()) return false;
	if (!force_repair()) return false;
	if (isUnRepairalbe()) return false;
	return true;
}

// private functions
uint32_t SubArray::key_maxVal(map<uint32_t, uint32_t>& cnt)
{
	map<uint32_t, uint32_t>::iterator it = cnt.begin();
	map<uint32_t, uint32_t>::iterator max = it;
	while (it != cnt.end())
	{
		if (it->second > max->second) max = it;
		it++;
	}
	return max->first;
}
void SubArray::update_codeWordErrCnt()
{
	codeWordErrCnt.clear();
	for (uint32_t i = 0; i < errBitMap.size(); i++)
	{
		uint32_t cwNum = errBitMap[i].row * nCodeWordsPerRow + errBitMap[i].col / lenCodeWord;
		codeWordErrCnt[cwNum] += 1;
	}
	for(uint32_t i = 0; i < singleFault.size(); i++)
	{
		uint32_t cwNum = singleFault[i].row * nCodeWordsPerRow + singleFault[i].col / lenCodeWord;
		codeWordErrCnt[cwNum] += 1;
	}
}
uint32_t SubArray::sing_error_num(void) 
{ 
	return errBitMap.size();
}; // number of single errors
// number of cluster errors
uint32_t SubArray::rowClst_error_num(void)	{ return clstErrRow.size(); }
uint32_t SubArray::colClst_error_num(void) { return clstErrCol.size(); }
uint32_t SubArray::total_error_num(void){
	return sing_error_num() + clstErrRow.size() + clstErrCol.size()+singleFault.size();
}
uint32_t SubArray::row_with_most_sngErrs() { return key_maxVal(rowErrCnt); }
uint32_t SubArray::col_with_most_sngErrs() { return key_maxVal(colErrCnt); }

uint32_t SubArray::errors_in_row(uint32_t row) {
	if (rowErrCnt.count(row)) return rowErrCnt[row];
	return 0;
}
uint32_t SubArray::errors_in_col(uint32_t col) {
	if (colErrCnt.count(col)) return colErrCnt[col];
	return 0;
}

void SubArray::initial()
{
	clstErrRow.clear();
	clstErrCol.clear();
	errBitMap.clear();
	rowErrCnt.clear();
	colErrCnt.clear();
	codeWordErrCnt.clear();
	singleFault.clear();
	repairedRows.clear();
	repairedCols.clear();
}

int SubArray::bitMap_delete_row(uint32_t row)
{
	int deleted = 0;
	for (size_t i = 0; i < errBitMap.size(); i++)
	{
		if (errBitMap[i].row == row)
		{
			uint32_t col = errBitMap[i].col;
			colErrCnt[col]--;
			errBitMap.erase(errBitMap.begin() + i);
			i--;
			deleted++;
		}
	}
	rowErrCnt.erase(row);
	return deleted;
}

int SubArray::bitMap_delete_col(uint32_t col)
{
	int deleted = 0;
	for (size_t i = 0; i < errBitMap.size(); i++)
	{
		if (errBitMap[i].col == col)
		{
			uint32_t row = errBitMap[i].row;
			rowErrCnt[row]--;
			errBitMap.erase(errBitMap.begin() + i);
			i--;
			deleted++;
		}
	}
	colErrCnt.erase(col);
	return deleted;
}

void SubArray::print_errBitMap(){
	cout << "rowErrCnt: ";
	for (map<uint32_t, uint32_t>::iterator it = rowErrCnt.begin(); it != rowErrCnt.end(); ++it)
	{
		cout << "(" << it->first << ":" << it->second << ")";
	}
	cout << endl;
	cout << "colErrCnt: ";
	for (map<uint32_t, uint32_t>::iterator it = colErrCnt.begin(); it != colErrCnt.end(); ++it)
	{
		cout << "(" << it->first << ":" << it->second << ")";
	}
	cout << endl;
	cout << "Single Errors:" << errBitMap.size() << endl;
	for (size_t i = 0; i < errBitMap.size(); i++)
	{
		cout << "<" << errBitMap[i].row << ", " << errBitMap[i].col << "> " << endl;
	}
}

void SubArray::update_errCnt()
{
	//#ifdef DEBUG
	//	cout << "update_errCnt() " << endl;
	//#endif
	rowErrCnt.clear();
	colErrCnt.clear();
	for (uint32_t i = 0; i < errBitMap.size(); ++i)
	{
		uint32_t row = errBitMap[i].row;
		uint32_t col = errBitMap[i].col;
		rowErrCnt[row] += 1;
		colErrCnt[col] += 1;
	}
}

void SubArray::show_state()
{
	using namespace std;
	cout << "------------------------------------------------" << endl;
	cout << "nAvaSpRows:" << nAvaSpRows << "  nAvaSpCols:" << nAvaSpCols << endl;
	cout << "nRowErrors:" << clstErrRow.size() << endl;
	for (set<int>::iterator it = clstErrRow.begin(); it != clstErrRow.end(); ++it) cout << *it << " ";
	cout << endl;
	cout << "nColErrors: " << clstErrCol.size() << endl;
	for (set<int>::iterator it = clstErrCol.begin(); it != clstErrCol.end(); ++it) cout << *it << " ";
	cout << endl;
	print_errBitMap();
	print_repairSolution();
	cout << "codeWordErrCnt: #Num: Cnt" << endl;
	map<uint32_t, uint32_t>::iterator it = codeWordErrCnt.begin();
	while (it != codeWordErrCnt.end())
	{
		cout << "#" << it->first << ":" << it->second << endl;
		it++;
	}
}

void SubArray::print_repairSolution()
{
	cout << "reapairedRows: ";
	for (uint32_t i = 0; i < repairedRows.size(); ++i) 
		cout << repairedRows[i] << " ";
	cout << endl;
	cout << "repairedCols: ";
	for (uint32_t i = 0; i < repairedCols.size(); ++i) 
		cout << repairedCols[i] << " ";
	cout << endl;

}

bool SubArray::isECCCorrectable()
{
	map<uint32_t, uint32_t>::iterator it = codeWordErrCnt.begin();
	while(it != codeWordErrCnt.end())
	{
		if(it->second > ECCCap)
		{
			return false;	
		}
		it++;
	}
	return true;;
}


void SubArray::single_fault_filter()
{
	vector<ErrorNode>::iterator it = errBitMap.begin();
	for(; it!= errBitMap.end(); ++it)
	{
		uint32_t row = it->row;
		uint32_t col = it->col;
		if((rowErrCnt[row] == 1) && (colErrCnt[col] == 1))
		{
			singleFault.push_back(ErrorNode(row,col));
			errBitMap.erase(it);
			it--;
		}
	}
	update_errCnt();
}


bool SubArray::isUnRepairalbe()
{
	return (singleFault.size() > nAvaSpCols + nAvaSpRows);
}

void SubArray::single_faults_repair()
{
	vector<ErrorNode>::iterator it = singleFault.begin();
	while(it!=singleFault.end())
	{
		if(nAvaSpRows == 0 && nAvaSpCols == 0) return;
		if(nAvaSpRows != 0)
		{
			uint32_t row = it->row;
			repairedRows.push_back(row);
			singleFault.erase(it);
			nAvaSpRows--;
			continue;
		}
		if (nAvaSpCols != 0)
		{
			uint32_t col = it->col;
			repairedCols.push_back(col);
			singleFault.erase(it);
			nAvaSpCols--;
			continue;
		}
	}
	update_codeWordErrCnt();
}
