#ifndef _EUCDSUB_H_
#define _EUCDSUB_H_
#include "SubArray.h"
#include "EUCW.h"

class EUCDSub
{
	public: 
		EUCDSub();
		EUCDSub(const SubArray& sub);
		EUCDSub(const EUCDSub& sub);
		~EUCDSub();

		virtual bool repair_with_spare_row(uint32_t eRow);
		virtual bool repair_with_spare_col(uint32_t eCol);

		void delete_EUCDs_in_row(uint32_t eRow);
		void delete_EUCDs_in_col(uint32_t eCol);

		void update_EUCDs(void);

		virtual void initial();
		void identify_EUCWs_and_EUCDs(const SubArray& sub);

	public:
		vector<EUCW> EUCWs;
		vector<ErrorNode> EUCDs;
		vector<uint32_t> repairedRows;
		vector<uint32_t> repairedCols;
		uint32_t nAvaSpRows;
		uint32_t nAvaSpCols;
};

#endif
