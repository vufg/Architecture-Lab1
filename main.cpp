#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

#include "instrctions.h"
#include "io.h"
#include "one_cycle_simulator.h"

using namespace std;

int imemory[127] = {0};
int dmemory[127] = {0}, reg[31] = {0};
int pc = 0, hi = 0, lo = 0;

int cycle = 0;
bool mul_flag = false, quit_flag = false, reg_changed[32], hi_changed, lo_changed, pc_changed;

FILE *snapshot, *error_dump;

void open_output_file(void){
    snapshot = fopen("snapshot.rpt", "w+");
    error_dump = fopen("error_dump.rpt", "w+");
}


int main(){
    int cmd;
    open_output_file();
    input_data_file();
    //int sv;

    do{
        output_register();
        cmd = imemory[pc/4];

        if(false){
            printf("cycle %d: 0x%08X \n", cycle+1, cmd);
        }

        pc_access(pc+4, 1);
        cycle++;
        one_cycle_simulator(cmd);

    }while(!quit_flag);

    close_output_file();

    return 0;
}

