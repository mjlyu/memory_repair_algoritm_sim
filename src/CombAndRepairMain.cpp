// file name: main.cpp
// main function of solution

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include "parameters.h"
#include "CombAndRepair.h"


using namespace std;

int main()
{
	cout << "***************************************************" << endl;
	cout << "Simulation started at: ";
	get_time();
	cout << "***************************************************" << endl;
	show_parameters();

	srand((unsigned int)time(NULL));
	for (double dens = StartDens; dens <= MaxDens; dens += densStep)
	{
		cout << "Density= " << dens << endl;
		//double  Prob = 1 / (1 + Area*dens / Alpha);
		int nGoodDie = 0;
		double nSumErrs = 0;
		for (int sim = 1; sim <= nSim; sim++)
		{
			if (sim % (nSim / 50) == 0) cerr << ">";
			//uint32_t nErrs = nbinrnd(Alpha, Prob);
			uint32_t nErrs = dens;
			nSumErrs += nErrs;
			SubArray sub(nErrs);
			//EUCDSub EUSub(sub);
			//IEUCWFilteredSub EUSub(sub);
			IEUCDFilteredSub EUSub(sub);
			CombAndRepair combBST(EUSub);
			combBST.BST_repair();
			nGoodDie += combBST.isRepaired();
		}
		double RepairRate = double(nGoodDie) / double(nSim);
		cout << endl;
		cout << "Dens = " << dens;
		cout << ", Average nErrs = " << nSumErrs / nSim;
		cout << ", RepairRate = " << RepairRate << endl;
		// print to file
	}
	cout << "***************************************************" << endl;
	cout << "Simulation finished at: ";
	get_time();
	return 0; // simulation exit correctly
};// end main
