#ifndef _IEUCDFILTEREDSUB_H_
#define _IEUCDFILTEREDSUB_H_

#include "IEUCWFilteredESub.h"

class IEUCDFilteredSub:public IEUCWFilteredSub
{
	public:
		IEUCDFilteredSub();
		IEUCDFilteredSub(const SubArray&);
		IEUCDFilteredSub(const IEUCWFilteredSub&);
		IEUCDFilteredSub(const IEUCDFilteredSub&);
		~IEUCDFilteredSub();

		virtual bool repair_with_spare_col(uint32_t eCol);

		void isolated_EUCD_filter(void);

	public:

};

#endif
