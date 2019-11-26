// 
/// Copyright (c) 2018 Xi'an Jiaotong University.
/// 
/// Unpublished copyright. All rights reserved. This material contains
// proprietary information that should be used or copied only within
// Xi'an Jiaotong University, except with written permission of Xi'an Jiaotong University.
// 
/// @file parameters.h
/// @brief: Simulation parameters
/// @author Minjie Lyu, major.lyu@foxmail.com
/// @version 1.0
/// @date 2018-03-28
#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

//system selection
#define OS_Linux 
//#define System_Windows

// memory architecture parameters
const int nBnksPerDie = 8; // number of banks per die
const int nBlksPerBnk = 32; // number of blocks per bank
const int nSubsPerBlk = 32; // number of subarrays per block
const int nRowsPerSub = 512;
const int nCodeWordsPerRow = 4;
const int nSpRowsPerSub = 6;
const int nSpColsPerSub = 6;
const int lenCodeWord = 128 + 8;
const int nColsPerSub = lenCodeWord * nCodeWordsPerRow;
const int ECCCap = 1;
const double RowCoeff = 0.00;
const double ColCoeff = 0.00;
//simulation parameters
const int nSim = 1000;
const double rRatio = 0;
const double cRatio = 0;
const double sRatio = 1 - rRatio - cRatio;

const double Alpha = 100;
const double StartDens = 130;
const double densStep = 10;
const double MaxDens = 260;
//const int nDens = 10;
const double Area = 1;

#endif
