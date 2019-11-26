#ifndef _EUCW_H_ 
#define _EUCW_H_ 
#include "SubArray.h"

class EUCW
{
public:
  EUCW();
  EUCW(uint32_t n);
	EUCW(const EUCW&);
  ~EUCW();
	void update_PRDCombs();

  void print();

public:
	uint32_t nErrs;
	vector<ErrorNode> Errors;
	vector<vector<int>> PRDCombs;
};

#endif
