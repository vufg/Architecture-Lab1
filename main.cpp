#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

#include "instrctions.h"
#include "io.h"
#include "one_cycle_simulator.h"

using namespace std;


int imemory[127] = {0}, dmemory[127] = {0}, reg[31] = {0};
int pc = 0, hi = 0, lo = 0;

int mul_flag = false, quit_flag = false, cycle = 0;

FILE *snapshot, *error_dump;

void open_input_file(void){
    snapshot = fopen("snapshot.rpt", "w+");
    error_dump = fopen("error_dump.rpt", "w+");
}


int main(){
    int cmd;
    open_input_file();
    input_data_file();

    do{
        cmd = imemory[pc/4];
        one_cycle_simulator(cmd);
    }while(!quit_flag);

    close_output_file();

    return 0;
}

