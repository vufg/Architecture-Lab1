#include "io.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

int dmemory_acess(int address, int value, int len, int write_enable){
    if(address < 0 || address > 1023){
        fprintf(error_dump , "In cycle %d: Address Overflow\n", cycle);
        //printf("In cycle %d: Address Overflow\n", cycle);
        quit_flag = true;
        return 0;
    }
    if(address % len){
        fprintf(error_dump , "In cycle %d: Misalignment Error\n", cycle);
        //printf("In cycle %d: Misalignment Error\n", cycle);
        quit_flag = true;
        return 0;
    }
    int tmp = dmemory[address/4];
    if(len == 4) {
        if(write_enable){
            tmp = value;
            dmemory[address/4] = tmp;
        }else{
            return tmp;
        }


    }else if(len == 2){
        if(write_enable)
        {
            if(address % 4 == 2){
                tmp = tmp & 0x0000FFFF;
                tmp = tmp | (value << 16);
            }else{
                tmp = tmp & 0xFFFF0000;
                tmp = tmp | value;
            }
            dmemory[address/4] = tmp;
        }else
        {
            if(address % 4 == 2){
                return ((unsigned int)tmp) >> 16;
            }else{
                return ((unsigned int)tmp) << 16 >> 16;
            }
        }

    }else if(len == 1){
        int shift = address % 4;
        if(write_enable){
            int mask = 0x000000FF;
            mask = mask << (shift * 8);
            mask = ~mask;
            tmp = tmp & mask;
            value = value & 0x000000FF;
            tmp = tmp | (value << (shift * 8));
            dmemory[address/4] = tmp;
        }else{
            return ((unsigned int)tmp) << ( (3 - shift) * 8) >> 24;
        }
    }
    return 0;
}

int register_acess(int address, int value, int write_enable){

    if(address == 0 and write_enable){
        fprintf(error_dump , "In cycle %d: Write $0 Error\n", cycle);
        printf("In cycle %d: Write $0 Error\n", cycle);
        return 0;
    }
    if(write_enable){
        reg[address] = value;
        return 0;
    }else{
        return reg[address];
    }
}

bool overflow_f(int s, int a, int b){
        s = s >> 31;
        a = s >> 31;
        b = b >> 31;
        if( !(a ^ b) && (s^a) ){
            fprintf(error_dump , "In cycle %d: Number Overflow\n", cycle);

            return true;
        }
        return false;
}

void input_data_file(void){

    const char *ifile = "iimage.bin";
    const char *dfile = "dimage.bin";
    unsigned int inst;

    std::ifstream iimage(ifile, std::fstream::in);
    std::ifstream dimage(dfile, std::fstream::in);

    //input dimage.bin
    dimage >> std::hex >> inst;
    register_acess(31, inst, 1);
    dimage >> std::hex >> inst;
    int num_dimage = inst;

    for(int ii = 0; ii < num_dimage; ii++){
        dimage >> std::hex >> inst;
        dmemory_acess(ii * 4, inst, 4, 1);
    }

    //input iimage.bin
    iimage >> std::hex >> inst;
    pc = inst;
    iimage >> std::hex >> inst;
    int num_iimage = inst;

    for(int ii = 0; ii < num_iimage; ii++){
        iimage >> std::hex >> inst;
        imemory[ii] = inst;
    }


    ///fprintf(error_dump, "%X\n", inst);

    ///fprintf(snapshot, "%X\n", inst);}

    return ;
}

void close_output_file(void){
    fclose(snapshot);
    fclose(error_dump);
}
