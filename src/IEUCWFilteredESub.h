#ifndef _IEUCWFILTEREDESUB_H_
#define _IEUCWFILTEREDESUB_H_
#include "EUCDSub.h"
class IEUCWFilteredSub:public EUCDSub
{
	public:
		IEUCWFilteredSub();
		IEUCWFilteredSub(const SubArray&);
		IEUCWFilteredSub(const EUCDSub&);
		IEUCWFilteredSub(const IEUCWFilteredSub&);
		~IEUCWFilteredSub();
		

		bool IEUCWs_repair(); // repair isolated EUCWs with remaining spares
		bool must_repair();
		bool early_abort();

		virtual bool repair_with_spare_row(uint32_t eRow);
		virtual bool repair_with_spare_col(uint32_t eCol);


		void isolated_EUCW_filter(void);
		virtual void initial(void);
		void update_EUCDCnt(void);
		void update_rowEUCWCnt(void);
		void update_EUCDsInIEUCWs(void);


	public:
		vector<EUCW> IEUCWs; // isolated EUCWs
		vector<ErrorNode> EUCDsInIEUCWs; // EUCDs in isolated EUCWs
		map<uint32_t, uint32_t> rowEUCDCnt;
		map<uint32_t, uint32_t> colEUCDCnt;
		map<uint32_t, uint32_t> rowEUCWCnt;


};

#endif
