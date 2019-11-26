#ifndef _COMPHELPER_H_
#define _COMPHELPER_H_
#include "EUCW.h"

class CompLess
{
	public:
		bool operator ()(const EUCW& pstItem1, const EUCW& pstItem2)
		{
			return pstItem1.nErrs < pstItem2.nErrs;
		}
};

class CompGreater
{
	public:
		bool operator ()(const EUCW& pstItem1, const EUCW& pstItem2)
		{
			return pstItem1.nErrs > pstItem2.nErrs;
		}

};


#endif
