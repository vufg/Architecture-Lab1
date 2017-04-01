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

void open_output_file(string foldname){
    string filepath = "C:/Users/Zhufeng/Desktop/project1_pdfs/valid_testcase/";
    string tmp_string;

    tmp_string = filepath + foldname + "/snapshot_mine.rpt";
    snapshot = fopen(tmp_string.c_str(), "w+");

    tmp_string = filepath + foldname + "/error_dump_mine.rpt";
    error_dump = fopen(tmp_string.c_str(), "w+");
}


int main(){

    DIR *dir;
    int cnt = 0;
    struct dirent *ent;
    string filepath = "C:/Users/Zhufeng/Desktop/project1_pdfs/valid_testcase/";
    if ((dir = opendir(filepath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            cnt++;
            printf("%s\n", ent->d_name);
            if(strlen(ent->d_name) < 5){
                //closedir(dir);
                continue;
            }

            for(int i = 0; i < 280; i++){
                imemory[i] = 0;
                dmemory[i] = 0;
            }

            for(int i = 0; i < 40; i++){
                reg[i] = 0;
            }
            pc = 0;
            hi = 0;
            lo = 0;
            cycle = 0;
            mul_flag = false;
            quit_flag = false;


            open_output_file(ent->d_name);
            input_data_file(ent->d_name);
            //int sv;

            do{
                output_register();

                //if(cycle == 1882){
                if(0){
                    printf("cycle %d: 0x%08X \n", cycle, global_cmd);
                    printf("mem[%d]: 0x%08X \n", cycle, dmemory[7]);
                    int stopword;
                    cin >>  stopword;
                    return 0;
                    //printf("reg[3]: 0x%08X\n", reg[3]);
                }

                global_cmd = imemory[pc/4];

                pc_access(pc+4, 1);
                cycle++;
                one_cycle_simulator(global_cmd);




            }while(!quit_flag);

            close_output_file();

    }
      closedir (dir);
    //      cout << cnt << endl;
    }



    return 0;
}

