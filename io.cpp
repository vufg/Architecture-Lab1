#include "io.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

//no matter many bytes dmemory_access get or return
//always in unsigned int form
//all 0 in the left for half word or byte operation
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
                tmp = tmp & 0xFFFF0000;
                tmp = tmp | (value & 0x0000FFFF);
            }else{
                tmp = tmp & 0x0000FFFF;
                tmp = tmp | (value << 16);
            }
            dmemory[address/4] = tmp;
        }else
        {
            if(address % 4 == 2){
                return ((unsigned int)tmp) << 16 >> 16;
            }else{
                return ((unsigned int)tmp) >> 16;
            }
        }

    }else if(len == 1){
        int shift = address % 4;
        if(write_enable){
            int mask = 0xFF000000;
            mask = mask >> (shift * 8);
            mask = ~mask;
            tmp = tmp & mask;
            value = value & 0x000000FF;
            tmp = tmp | (value << ((3 - shift) * 8));
            dmemory[address/4] = tmp;
        }else{
            return ((unsigned int)tmp) << ( shift * 8) >> 24;
        }
    }
    return 0;
}

int register_acess(int address, int value, int write_enable){

    if(address == 0 and write_enable){
        fprintf(error_dump , "In cycle %d: Write $0 Error\n", cycle);
        //printf("In cycle %d: Write $0 Error\n", cycle);
        return 0;
    }
    if(write_enable){
        if(reg[address] != value){
            reg_changed[address] = true;
            reg[address] = value;
        }
        return 0;
    }else{
        return reg[address];
    }
}

int pc_access(int value, int write_enable){
    if(write_enable){
        if(pc != value){
            pc_changed = true;
            pc = value;
        }

    }
    return 0;
}

int hi_access(int value, int write_enable){
    if(write_enable){
        if(hi != value){
            hi_changed = true;
            hi = value;
        }

    }
    return 0;
}

int lo_access(int value, int write_enable){
    if(write_enable){
        if(lo != value){
            lo = value;
            lo_changed = true;
        }
    }
    return 0;
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


unsigned int change_endian(unsigned int num){
    unsigned int ans = 0;
    //cout << bitset<32>(num) << endl << endl;
    for(int i = 0; i < 4; i++){
        ans = ans | (num << (i << 3) >> 24 << (i << 3));
    }
    return ans;
}

void input_data_file(void){

    FILE *iimage_file, *dimage_file;
    unsigned int inst, num_dimage, num_iimage;

    //initial several change marks to prepare for snapshot.rpt
    for(int i = 0; i < 32; i++)
        reg_changed[i] = true;
    hi_changed = true;
    lo_changed = true;
    pc_changed = true;



    //open input files
    iimage_file = fopen("iimage.bin", "rb+");
    dimage_file = fopen("dimage.bin", "rb+");


    fread(&inst, sizeof(unsigned int), 1, dimage_file);
    register_acess(29, change_endian(inst), 1);
    //printf("0x%08X\n", change_endian(inst));

    fread(&inst, sizeof(unsigned int), 1, dimage_file);
    num_dimage = change_endian(inst);
    //printf("num_dimage: %X\n", num_dimage);
    //printf("inst: %X\n", inst);

    for(unsigned int ii = 0; ii < num_dimage; ii++){
        fread(&inst, sizeof(unsigned int), 1, dimage_file);
        //dmemory_acess(ii * 4, change_endian(inst), 4, 1);
        dmemory_acess(ii * 4, change_endian(inst), 4, 1);
    }


    //input iimage.bin
    fread(&inst, sizeof(unsigned int), 1, iimage_file);
    pc = change_endian(inst);

    fread(&inst, sizeof(unsigned int), 1, iimage_file);
    num_iimage = change_endian(inst);


    //std::cout << "iimage\n\n";
    for(unsigned int ii = 0; ii < num_iimage; ii++){
        fread(&inst, sizeof(unsigned int), 1, iimage_file);
        imemory[pc/4 + ii] = change_endian(inst);
        //std::cout << ii << ":  " << std::hex << imemory[ii] << "\n";
    }

    //std::cout << "\n\n\n wait...\n";
    //int sw;
    //std::cin >> sw;

    fclose(iimage_file);
    fclose(dimage_file);

    return ;
}

void output_register(void){
    fprintf(snapshot, "cycle %d\n", cycle);
    bool no_change = true;
    for(int i = 0; i < 32; i++)
        if(reg_changed[i]){
            fprintf(snapshot, "$%.2d: 0x%08X\n", i, reg[i]);
            reg_changed[i] = false;
            no_change = false;
        }
    if(hi_changed){
        fprintf(snapshot, "$HI: 0x%08X\n", hi);
        hi_changed = false;
        no_change = false;
    }

    if(lo_changed){
        fprintf(snapshot, "$LO: 0x%08X\n", lo);
        lo_changed = false;
        no_change = false;
    }

    if(pc_changed || no_change){
        fprintf(snapshot, "PC: 0x%08X\n", pc);
        pc_changed = false;
    }

    fprintf(snapshot, "\n\n");


}

void close_output_file(void){
    fclose(snapshot);
    fclose(error_dump);
}
