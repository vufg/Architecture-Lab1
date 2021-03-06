#ifndef ONE_CYCLE_SIMULATOR_H_INCLUDED
#define ONE_CYCLE_SIMULATOR_H_INCLUDED

#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

extern int imemory[127];
extern int dmemory[127], reg[31];
extern int pc, hi, lo;
extern bool mul_flag, quit_flag;
extern int  cycle;
extern FILE *snapshot, *error_dump;


int one_cycle_simulator(int cmd);

#endif // ONE_CYCLE_SIMULATOR_H_INCLUDED
