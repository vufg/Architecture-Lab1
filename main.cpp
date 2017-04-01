#include <string>
#include <cstdio>
#include "instructions.h"
#include "io.h"
#include "one_cycle_simulator.h"
#include <string.h>
#include <dirent.h>

using namespace std;

int imemory[300] = {0};
int dmemory[300] = {0};
int reg[50] = {0};
int pc = 0, hi = 0, lo = 0;

int cycle = 0;
bool mul_flag = false, quit_flag = false, reg_changed[32], hi_changed, lo_changed, pc_changed;

int global_cmd;

FILE *snapshot, *error_dump;

void open_output_file(void){
    snapshot = fopen("snapshot.rpt", "w+");
    error_dump = fopen("error_dump.rpt", "w+");
}


int main(){
    open_output_file();
    input_data_file();
    do{

        output_register();
        global_cmd = imemory[pc/4];
        pc_access(pc+4, 1);

        cycle++;
        one_cycle_simulator(global_cmd);


    }while(!quit_flag);

    close_output_file();


    return 0;
}

