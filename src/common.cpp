// 
/// Copyright (c) 2018 Xi'an Jiaotong University.
/// 
/// Unpublished copyright. All rights reserved. This material contains
// proprietary information that should be used or copied only within
// Xi'an Jiaotong University, except with written permission of Xi'an Jiaotong University.
// 
/// @file common.cpp
/// @brief: Common functions
/// @author Minjie Lyu, major.lyu@foxmail.com
/// @version 1.0
/// @date 2018-03-28

#include "common.h"
using namespace std;
uint32_t index_maxVal(map<uint32_t, uint32_t>& cnt)
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

EType error_type()
{
  double rnd = (double)rand()/(double)RAND_MAX;
  if (rnd < rRatio) return rowErr;
  else if(rnd < rRatio+cRatio) return colErr;
  else return sngErr;
};

void get_time() // print the current time
{
  using namespace std;
#ifdef OS_Linux
  time_t time1;
  time(&time1);
  cout << (asctime(localtime(&time1)));
#endif
#ifdef OS_Windows
  char tmp[64];
  struct tm t;    
  time_t now;     
  time(&now);     
  localtime_s(&t, &now);   
  strftime(tmp, sizeof(tmp), "%X %a, %b %d, %Y", &t);
  cout << endl;
  cout << tmp;
#endif
};

bool lessCMP(const PAIR &x, const PAIR &y)
{
  return x.second > y.second;
}
bool greaterCMP(const PAIR &x, const PAIR &y)
{
  return x.second < y.second;
}

int nbinrnd(double r, double p)
{
  int rnd = 0;
  long fr = 0;
  while (fr<r)
  {
    double pV = (double)rand() / (double)RAND_MAX;
    pV >= p ? rnd++ : fr++;

  }
  return rnd;
};
void show_parameters()
{
	using namespace std;
	cout << "Rows: " << nRowsPerSub << ", Cols: "<< nColsPerSub;
	cout << ", SpareRows: " << nSpRowsPerSub << ", SpareCols: " << nSpColsPerSub << endl;
	cout << "StartDens:" << StartDens << ", nSim: " << nSim << ", MaxDens: "<< MaxDens << endl;
}
