#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>


extern int imemory[127], dmemory[127], reg[31];
extern int pc, hi, lo;
extern int mul_flag, quit_flag , cycle;
extern FILE *snapshot, *error_dump;


int dmemory_acess(int address, int value, int len, int write_enable);
int register_acess(int address, int value, int write_enable);

bool overflow_f(int s, int a, int b);

void input_data_file(void);
void close_output_file(void);

#endif // IO_H_INCLUDED
