#ifndef _DESCARTE_H_
#define _DESCARTE_H_

#include <vector>
#include <stdint.h>
using namespace std;

void decare(const vector< vector<int> >& Sets, vector< vector<uint32_t> >& rs);
void descarte(const vector<uint32_t>& Ns, vector<vector<uint32_t>>& rs);

#endif
