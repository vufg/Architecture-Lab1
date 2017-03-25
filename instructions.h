#ifndef INSTRCTIONS_H_INCLUDED
#define INSTRCTIONS_H_INCLUDED

#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

extern int imemory[300];
extern int dmemory[300];
extern int reg[50];

extern int pc, hi, lo;
extern bool mul_flag, quit_flag;
extern int  cycle;
extern FILE *snapshot, *error_dump;



    int add(int rd, int rs, int rt);

    int addu(int rd, int rs, int rt);

    int sub(int rd, int rs, int rt);

	int and_f(int rd, int rs, int rt);

	int or_f(int rd, int rs, int rt);

	int xor_f(int rd, int rs, int rt);

	int nor_f(int rd, int rs, int rt);

	int nand_f(int rd, int rs, int rt);

	int slt(int rd, int rs, int rt);


	///shift operations
	int sll(int rd, int rt, int shamt);

	int srl(int rd, int rt, int shamt);

	int sra(int rd, int rt, int shamt);

	int jr(int rs);

	int mult(int rs, int rt);

	int multu(int rs, int rt);

	int mfhi(int rd);

	int mflo(int rd);

	int jump(unsigned int address);

	int jal(unsigned int address);

    ///immediate calculations
	int addi(int rt, int rs, int immediate);

	int addiu(int rt, int rs, int immediate);

	int lw(int rt, int rs, int immediate);

	int lh(int rt, int rs, int immediate);

	int lhu(int rt, int rs, int immediate);

	int lb(int rt, int rs, int immediate);

	int lbu(int rt, int rs, int immediate);

	int sw(int rt, int rs, int immediate);

	int sh(int rt, int rs, int immediate);

	int sb(int rt, int rs, int immediate);

	int lui(int rt, int immediate);

	int andi(int rt, int rs, int immediate);

	int ori(int rt, int rs, int immediate);

	int nori(int rt, int rs, int immediate);

	int slti(int rt, int rs, int immediate);

	int beq(int rs, int rt, int immediate);

	int bne(int rs, int rt, int immediate);

	int bgtz(int rs, int immediate);

	int halt_f(void);

#endif // INSTRCTIONS_H_INCLUDED
