
// file name: main.cpp
// main function of solution

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <time.h>
#include <getopt.h>
#include "common.h"

#include "parameters.h"
#include "CombAndRepair.h"
#include "HeuristicRepair.h"

using namespace std;

void usage()
{
	cout << "RuntimeMain Usage: "<< endl;
	cout << "RuntimeMain -a algorithm[Heuristic/CombBST/HST/HSR_DFS] -t technique[NONE/IWF/IDF]" << endl;
	cout << "\t-a --algorithm=ALGORITHM \tspecify a algorithm to be test" << endl;
	cout << "\t-t --techique=TECHNIQUE \tspecify Filter technique" << endl;
}

ALG alg = Heuristic;
TECH tech = NONE;

void parameter_parse(int argc, char** argv);
void print_runtime_parameters();

int main(int argc, char** argv)
{
	parameter_parse(argc, argv);
	cout << "***************************************************" << endl;
	cout << "Simulation started at: ";
	get_time();
	cout << "***************************************************" << endl;
	show_parameters();
	print_runtime_parameters();

	int nGoodDies;
	int nErrs;


	srand((unsigned int)time(NULL));
	for (double dens = StartDens; dens<= MaxDens; dens+=densStep)
	{
		nGoodDies = 0;
		nErrs = dens;
		//nErrs = nbinrnd(dens, Alpha);
		for (int sim = 1; sim <= nSim; sim++)
		{
			if (sim % (nSim / 50) == 0) cerr << ">";
			SubArray sub(nErrs);

			switch(alg)
			{
				case(Heuristic):
					{
						HeuristicRepair Hsub(sub);
						nGoodDies+=Hsub.isRepaired();
						break;
					}
				case(CombBST):
					{
						switch(tech)
						{
							case(NONE):
								{
									EUCDSub ESub(sub);
									CombAndRepair arr(ESub);
									arr.BST_repair();
									nGoodDies += arr.isRepaired();
									break;
								}
							case(IWF):
								{
									IEUCWFilteredSub ESub(sub);
									CombAndRepair arr(ESub);
									arr.BST_repair();
									nGoodDies += arr.isRepaired();
									break;
								}
							case(IDF):
								{
									IEUCDFilteredSub ESub(sub);
									CombAndRepair arr(ESub);
									arr.BST_repair();
									nGoodDies += arr.isRepaired();
									break;
								}
						}
						break;
					}
				case(HST):
					{

						break;
					}
				case(HST_DFS):
					{

						break;
					}
			}
		}
		double repairRate = (double)nGoodDies/nSim;
		cout << "\nDefectDensity = " << dens;
		cout << " repairRate = " << repairRate*100 << "\%" << endl;
	}
	cout << "***************************************************" << endl;
	cout << "Simulation finished at: ";
	get_time();
	return 0; // simulation exit correctly
};// end main


void parameter_parse(int argc, char** argv)
{
	int c;
	// getopt stuff
	string temp("Heuristic");
	string temp2("NONE");
	while(1)
	{
		static struct option long_options[]=
		{
			{"algorithm", required_argument, 0, 'a'},
			{"technique", required_argument, 0, 't'},
			{"help", required_argument, 0, 'h'},
			{0, 0, 0, 0}
		};
		int option_index = 0; //for getopt
		c = getopt_long(argc, argv, "a:t:h", long_options, &option_index);
		if (c == -1)
		{
			break;
		}
		switch(c)
		{
			case 0:
				if (long_options[option_index].flag != 0)
				{
					cout << "setting flag" << endl;
					break;
				}
				cout << "option " << long_options[option_index].name;
				if (optarg)
				{
					cout << "with arg " << string(optarg);
				}
				cout << endl;
				break;
			case 'h':
				usage();
				exit(0);
				break;
			case 'a':
				temp = string(optarg);
				break;
			case 't':
				temp2 = string(optarg);
				break;
			case '?':
				usage();
				exit(-1);
				break;
		}
	}
	if (temp == "Heuristic")
	{
		alg = Heuristic;
	}
	else if (temp == "CombBST")
	{
		alg = CombBST;
	}
	else if (temp == "HST")
	{
		alg = HST;
	}
	else if (temp == "HST_DFS")
	{
		alg = HST_DFS;
	}
	else
	{
		ERROR("==Unkown Algorithm: " << temp);
		exit(0);
	}

	if (temp2 == "IWF")
	{
		tech = IWF;
	}
	else if (temp2 == "IDF")
	{
		tech = IDF;
	}
	else if (temp2 == "NONE")
	{
		tech = NONE;
	}
	else
	{
		ERROR("==Unkown Technique: " << temp2);
	}
}
void print_runtime_parameters()
{
	cout << "Algorithm: ";
	switch(alg)
	{
		case Heuristic:
			{
				cout << "Heuristic";
				break;
			}
		case CombBST:
			{
				cout << "Combination&BST";
				break;
			}
		case HST:
			{
				cout << "Hybrid Search Tree";
				break;
			}
		case HST_DFS:
			{
				cout << "HST with DFS";
				break;
			}
	};
	cout << ", Techniques: " ;
	switch(tech)
	{
		case(NONE):
			{
				cout << "nothing" << endl;
				break;
			}
		case (IWF):
			{
				cout << "isoalted EUCW Filter applied" << endl;
				break;
			}
		case (IDF):
			{
				cout << "isolated EUCW Filter and iolated EUCD Filter" << endl;
				break;
			}
	}
}
