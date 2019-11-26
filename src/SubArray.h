/*
 * SubArray.h
 *
 *  Created on: Apr 20, 2018
 *      Author: mjlyu
 */

#ifndef _SUBARRAY_H_
#define _SUBARRAY_H_

#include <vector>
#include <set>
#include <map>
#include <assert.h>
#include <stdint.h>
#include "common.h"


using namespace std;

struct ErrorNode
{
  uint32_t row;
  uint32_t col;
  ErrorNode(uint32_t r, uint32_t c) : row(r), col(c){};
};

class SubArray{
	public:// interface functions
		// error inject
		virtual void error_inject(uint32_t nErrs);
    void error_inject(const ErrorNode& err);
		// repair basic
		bool repair_with_sprow(uint32_t eRow); // repair an error with spare row
		bool repair_with_spcol(uint32_t eCol); // repair an error with spare column
		// repair
		//
		int repair_row(uint32_t eRow);// repair faulty eRow without considering spaare constraint;
		int repair_col(uint32_t eCol);//repair faulty eCol without considering spare constraint;
		bool cluster_repair(void); // repair cluster row/column errors
		bool force_repair(void); // force repair: single error must be repaired with
		//row/column spares
		uint32_t sing_error_num(void); // number of single errors
		// number of cluster errors
		uint32_t rowClst_error_num(void);	
		uint32_t colClst_error_num(void); 
		uint32_t total_error_num(void);
		uint32_t row_with_most_sngErrs();
		uint32_t col_with_most_sngErrs();
		uint32_t errors_in_row(uint32_t row); 
		uint32_t errors_in_col(uint32_t col); 
		virtual bool isECCCorrectable();
		//
		// operator reloading
		SubArray& operator=(const SubArray& rhs);

		//Constructors and Deconstructor
		SubArray();
		explicit SubArray(uint32_t nErrs);
		SubArray(const SubArray&);
   
		virtual ~SubArray();

		// functions for testing
		virtual void show_state();
    virtual void print_repairSolution();
		virtual bool repair();
		void single_fault_filter();
		bool isUnRepairalbe();
		void single_faults_repair();

    void update_codeWordErrCnt();
    void update_errCnt(void);
    int bitMap_delete_col(uint32_t eCol);
    int bitMap_delete_row(uint32_t eRow);
    void print_errBitMap(void);
    void initial();

private:
		// private functions
		void error_inject(uint32_t row, uint32_t col, EType t);
		uint32_t key_maxVal(map<uint32_t,uint32_t>&);
//********************************************************************//
public: // date structures
		uint32_t nAvaSpRows; // spare rows
		uint32_t nAvaSpCols; // spare columns
		set<int> clstErrRow; //<#row of cluster row erros>
		set<int> clstErrCol; //<#column of cluster column errors>
		vector<ErrorNode> errBitMap; // error bit map
		map<uint32_t, uint32_t> rowErrCnt; // the number of errors in each faulty row
		map<uint32_t, uint32_t> colErrCnt; // the number of errors in each faulty col
    map<uint32_t, uint32_t> codeWordErrCnt;
		vector<ErrorNode> singleFault; // single faulty cells, for sinlge fault filter
    vector<uint32_t> repairedRows; // rows repaired with spare rows
    vector<uint32_t> repairedCols; // columns repaired with spare columns
};

#endif /* SRC_SUBARRAY_H_ */
