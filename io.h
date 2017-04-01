#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

extern int global_cmd;

extern int imemory[300];
extern int dmemory[300];
extern int reg[50];

extern int pc, hi, lo;
extern bool mul_flag, quit_flag;
extern int  cycle;
extern FILE *snapshot, *error_dump;
extern bool reg_changed[32], hi_changed, lo_changed, pc_changed;


int dmemory_acess(int address, int value, int len, int write_enable);
int register_acess(int address, int value, int write_enable);
int pc_access(int value, int write_enable);
int hi_access(int value, int write_enable);
int lo_access(int value, int write_enable);


unsigned int change_endian(unsigned int num);

bool overflow_f(int a, int b, int error_drop);
void output_register(void);

void input_data_file(void);

void close_output_file(void);


#endif // IO_H_INCLUDED
