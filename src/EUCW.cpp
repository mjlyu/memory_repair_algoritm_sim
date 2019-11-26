#include "EUCW.h"
#include <iostream>
#include "CombTraversal.h"

using namespace std;

EUCW::EUCW()
{}

EUCW::EUCW(uint32_t n):nErrs(n)
{
	Errors.clear();
	update_PRDCombs();
}

EUCW::EUCW(const EUCW& eucw)
{
	nErrs = eucw.nErrs;
	Errors = eucw.Errors;
	PRDCombs = eucw.PRDCombs;
}

void EUCW::update_PRDCombs()
{
	PRDCombs.clear();
	combination(nErrs, nErrs-ECCCap, PRDCombs);
}

EUCW::~EUCW() {}
void EUCW::print()
{
	cout << "nErrs: " << nErrs << endl;
	// print errors
  for (size_t i = 0; i < Errors.size(); i++)
  {
    cout << "(" << Errors[i].row << "," << Errors[i].col << ")" << endl;
  }
	// print combs
	for(size_t i = 0; i < PRDCombs.size(); ++i)
	{
		for (size_t j = 0; j < PRDCombs[i].size(); ++j)
		{
			cout << PRDCombs[i][j] << " ";
		}
		cout << endl;
	}
}

