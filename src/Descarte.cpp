#include "Descarte.h"
#include <vector>

using namespace std;
void descarte(const vector<uint32_t>& ds, vector<vector<uint32_t>>& rs)
{
  vector< vector<int> > sets;
  for (uint32_t i = 0; i < ds.size(); i++)
  {
    vector<int> tmp;
    for (uint32_t j = 0; j < ds[i]; j++)
    {
      tmp.push_back(j);
    }
    sets.push_back(tmp);
  }
  decare(sets, rs);
}

void decare(const vector< vector<int> >& Sets, vector<vector<uint32_t>>& rs)
{
  int n = Sets.size();
  vector<uint32_t> tmp;
  for (int i = 0; i < n; ++i)
  {
    tmp.push_back(Sets[i][0]);
  }
  rs.push_back(tmp);

  for (int i = n - 1; i >= 0; --i)
  {
    int nRsSize = rs.size();
		int ss = Sets[i].size();
    for (int k = 1; k < ss; ++k)
    {
      for (int j = 0; j < nRsSize; ++j)
      {
        tmp = rs[j];
        tmp[i] = Sets[i][k];
        rs.push_back(tmp);
      }
    }
  }
}
