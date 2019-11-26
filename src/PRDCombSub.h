#ifndef _PRDCOMBSUB_H_
#define _PRDCOMBSUB_H_
#include "IEUCDFilteredSub.h"

class PRDCombSub:public IEUCWFilteredSub
{
	public:
		PRDCombSub();
		PRDCombSub(const EUCDSub&);
		PRDCombSub(const IEUCWFilteredSub&);
		PRDCombSub(const IEUCDFilteredSub&);
		~PRDCombSub();
		void create_PRDSub(SubArray& arr, uint32_t sel);
		size_t total_PRDCombs();


		virtual void initial();
	private:
		void construct_PRDCombs();
		void create_PRDBitMap(vector<ErrorNode>& PRDBitMap, uint32_t sel);
		void create_PRDSub(SubArray& arr, vector<ErrorNode>& PRDBitMap);
	

	private:
		vector<vector<uint32_t>> PRDCombs;

};

#endif
