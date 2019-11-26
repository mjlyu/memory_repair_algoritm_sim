// 
/// Copyright (c) 2018 Xi'an Jiaotong University.
/// 
/// Unpublished copyright. All rights reserved. This material contains
// proprietary information that should be used or copied only within
// Xi'an Jiaotong University, except with written permission of Xi'an Jiaotong University.
// 
/// @file common.h
/// @brief: common defines
/// @author Minjie Lyu, major.lyu@foxmail.com
/// @version 1.0
/// @date 2018-03-28
#ifndef _COMMON_H_
#define _COMMON_H_

#include <ctime>
#include <cstdlib>
#include <stdint.h>
#include <map>

#include <iostream>
#include <iomanip>
#include "parameters.h"

//#include <ctime>
//#define DEBUG 1
//
typedef std::pair<uint32_t,uint32_t> PAIR;
bool greaterCMP(const PAIR &x, const PAIR &y); // y.second > x.second
bool lessCMP(const PAIR &x, const PAIR &y); // y.second < x.second
typedef enum { rowErr, colErr, sngErr } EType; // error type

typedef enum { sRow, sCol, nRep} RType; //error repair type

enum ALG{
	Heuristic,
	CombBST,
	HST,
	HST_DFS
};

enum TECH
{
	NONE, // no technique applied
	IWF,  // isolated EUCW Filter
	IDF   // isolated EUCD Filter
};

#define ERROR(str) std::cerr << "[ERROR (" <<__FILE__<<__LINE__<<")]: "<<str << std::endl;

EType error_type();

int nbinrnd(double r, double p);

void get_time(); // print the current time
void show_parameters();
uint32_t index_maxVal(std::map<uint32_t,uint32_t>& mp);

#endif
