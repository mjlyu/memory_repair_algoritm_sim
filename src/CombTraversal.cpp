#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void printResult(vector<int>& vecInt, vector<int> t, vector<vector<int>>& rslt){
  vector<int> vec;
  for (uint32_t i = 0; i < vecInt.size(); ++i){
    if (vecInt[i] == 1){
      vec.push_back(t[i]);
      //cout << t[i] << " ";
    }
  }
  rslt.push_back(vec);
  //cout << endl;
}

bool compare(int a, int b){
  if (a > b){
    return true;
  }
  else{
    return false;
  }
}

void combination(vector<int>& t, int c, vector<vector<int>>& rslt){
  //initial first combination like:1,1,0,0,0
  int total = t.size();
  vector<int> vecInt(total, 0);
  for (int i = 0; i < c; ++i){
    vecInt[i] = 1;
  }

  printResult(vecInt, t, rslt);

  for (int i = 0; i < total - 1; ++i){
    if (vecInt[i] == 1 && vecInt[i + 1] == 0){
      //1. first exchange 1 and 0 to 0 1
      swap(vecInt[i], vecInt[i + 1]);

      //2.move all 1 before vecInt[i] to left
      sort(vecInt.begin(), vecInt.begin() + i, compare);

      //after step 1 and 2, a new combination is exist
      printResult(vecInt, t,rslt);

      //try do step 1 and 2 from front
      i = -1;
    }
  }
}

void combination(int N, int c, vector<vector<int>>& rslt)
{
  vector<int> t;
  for (int i = 0; i < N; i++)
    t.push_back(i);

  combination(t, c, rslt);
}


