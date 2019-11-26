#ifndef _HEURISTICREPAIR_H_
#define _HEURISTICREPAIR_H_
#include "IEUCWFilteredESub.h"

class HeuristicRepair:public EUCDSub
{
	public:
		HeuristicRepair(){};
		HeuristicRepair(const SubArray&);
		~HeuristicRepair();
		void repair();
		bool isRepaired();

	private:
		void initial();
		void update_PRDCnt();
		virtual bool repair_with_spare_row(uint32_t eRow);
		virtual bool repair_with_spare_col(uint32_t eCol);


	private:
		map<uint32_t, uint32_t>rowPRDCnt;
		map<uint32_t, uint32_t>colPRDCnt;
		bool isSucceed;

};

#endif
