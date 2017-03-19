#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int cmd, opcode;
int imemory[127] = {0};
int dmemory[127] = {0};
int reg[31] = {0};
int pc = 0, hi = 0, lo = 0;
int mul_flag = false;
int num_iimage, num_dimage;
bool quit_flag = false;
int cycle = 0;

int dmemory_acess(int address, int value, int len, int write_enable){
    if(address < 0 || address > 1023){
        //fprintf(file_ptr , "In cycle %d: Address Overflow\n", cycle);
        printf("In cycle %d: Address Overflow\n", cycle);
        quit_flag = true;
        return 0;
    }

    if(len == 4) {

    }else if(len == 2){

    }else if(len == 1){

    }


    if(write_enable){
        dmemory[address/4] = value;
    }else{
        return dmemory[address / 4];
    }
    return 0;
}

int register_acess(int address, int value, int write_enable){

    if(address == 0 and write_enable){
        //fprintf( file_ptr , "In cycle %d: Write $0 Error\n", cycle);
        printf("In cycle %d: Write $0 Error\n", cycle);
        return 0;
    }
    if(write_enable){
        reg[address] = value;
        return 0;
    }else{
        return reg[addres];
    }
}



/// instruction functions

    bool overflow_f(int s, int a, int b){
        s = s >> 31;
        a = s >> 31;
        b = b >> 31;
        if( !(a ^ b) && (s^a) ){
            //fprintf(file_ptr , "In cycle %d: Number Overflow\n", cycle);
            printf("In cycle %d: Number Overflow\n", cycle);
            return true;
        }
        return false;
    }



    int add(int rd, int rs, int rt){
        int ans = reg[rs] + reg[rt];
        register_acess(rd, ans, 1);
        overflow_f(ans, reg[rs], reg[rt]);
		return 0;
	}

	int addu(int rd, int rs, int rt){{
        unsigned int ans;
        ans = (unsigned)reg[rs] + (unsigned)reg[rt];
        register_acess(rd, ans, 1);
		return 0;
	}

	int sub(int rd, int rs, int rt){
        int ans = reg[rs] - reg[rt];
        register_acess(rd, ans, 1);
        overflow_f(ans, reg[rs], reg[rt]);
		return 0;
	}

	int and_f(int rd, int rs, int rt){
	    int ans;
	    ans = reg[rs] & reg[rt];
	    register_acess(rd, ans, 1);
		return 0;
	}

	int or_f(int rd, int rs, int rt){
	    int ans;
	    ans = reg[rs] | reg[rt];
	    register_acess(rd, ans, 1);
		return 0;
	}

	int xor_f(int rd, int rs, int rt){
	    int ans;
	    ans = reg[rs] ^ reg[rt];
	    register_acess(rd, ans, 1);
		return 0;
	}

	int nor_f(int rd, int rs, int rt){
	    int ans;
	    ans = ~(reg[rs] | reg[rt]);
	    register_acess(rd, ans, 1);
		return 0;
	}

	int nand_f(int rd, int rs, int rt){
	    int ans;
	    ans = ~(reg[rs] & reg[rt]);
	    register_acess(rd, ans, 1);
		return 0;
	}

	int slt(int rd, int rs, int rt){
	    int ans;
	    ans = (reg[rs] < reg[rt]);
	    register_acess(rd, ans, 1);
		return 0;
	}


	///shift operations
	int sll(int rd, int rt, int shamt){
	    int ans;
	    ans = reg[rt] << shamt;
	    register_acess(rd, ans, 1);
		return 0;
	}

	int srl(int rd, int rt, int shamt){
	    int ans;
	    ans = (unsigned int)reg[rt] >> shamt;
	    register_acess(rd, ans, 1);
		return 0;
	}

	int sra(int rd, int rt, int shamt){
	    int ans;
	    ans = reg[rt] >> shamt;
	    register_acess(rd, ans, 1);
		return 0;
	}

	int jr(int rs){
	    pc = reg[rs];
		return 0;
	}

	int mult(int rs, int rt){
	    if(mul_flag){
             fprintf(file_ptr , "In cycle %d: Overwrite HI-LO registers\n", cycle);
             printf("In cycle %d: Overwrite HI-LO registers\n", cycle);
	    }
	    mul_flag = true;
	    hi = (int)( ((long long)reg[rs] * (long long)reg[rt]) >> 32);
        lo = (int)( ((long long)reg[rs] * (long long)reg[rt]) << 32 >> 32);
        return 0;
	}

	int multu(int rs, int rt, int rd){
	    if(mul_flag){
             fprintf(file_ptr , "In cycle %d: Overwrite HI-LO registers\n", cycle);
             printf("In cycle %d: Overwrite HI-LO registers\n", cycle);
	    }
	    mul_flag = true;
	    hi = (unsigned int)( ((unsigned long long)reg[rs] * (unsigned long long)reg[rt]) >> 32);
        lo = (unsigned int)( ((unsigned long long)reg[rs] * (unsigned long long)reg[rt]) << 32 >> 32);
        return 0;
	}

	int mfhi(int rd){
	    mul_flag = false;
	    register_acess(rd, hi, 1);
		return 0;
	}

	int mflo(int rd){
	    mul_flag = false;
	    register_acess(rd, lo, 1);
		return 0;
	}

	int jump(int address){
	    pc = address;
		return 0;
	}

	int jal(int address){
	    register_acess(31, pc+4, 1);
	    pc = address;
		return 0;
	}

    ///immediate calculations
	int addi(int rt, int rs, int immediate){
	    int ans = reg[rs] + immediate;
        register_acess(rt, ans, 1);
        overflow_f(ans, reg[rs], immediate);
		return 0;
	}

	int addiu(int rt, int rs, int immediate){
		unsigned int ans = (unsigned)reg[rs]  + (unsigned int)immediate;
        register_acess(rt, ans, 1);
		return 0;
	}

	int lw(int rt, int rs, int immediate){
	    int tmp;
	    if(rt == 0){
            ///error detection of write register zero is prior to other error detections
            register_acess(rt, 0, 1);
	    }

	    tmp = dmemory_acess(reg[rs] + immediate, 0, 4, 0);
	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int lh(int rt, int rs, int immediate){
	    int tmp;
	    if(rt == 0){
            register_acess(rt, 0, 1);
	    }

	    tmp = dmemory_acess(reg[rs] + immediate, 0, 2, 0);
	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int lhu(int rt, int rs, int immediate){
	    int tmp;
	    if(rt == 0){
            register_acess(rt, 0, 1);
	    }

	    tmp = (unsigned int)dmemory_acess(reg[rs] + immediate, 0, 2, 0);
	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int lb(int rt, int rs, int immediate){
	    int tmp;
	    if(rt == 0){
            register_acess(rt, 0, 1);
	    }
	    tmp = dmemory_acess(reg[rs] + immediate, 0, 1, 0);
	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int lbu(int rt, int rs, int immediate){
	    int tmp;
	    if(rt == 0){
            register_acess(rt, 0, 1);
	    }

	    tmp = (unsigned int)dmemory_acess(reg[rs] + immediate, 0, 1, 0);
	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int sw(int rs, int rt, int immediate){
		return 0;
	}

	int sh(int rs, int rt, int immediate){
		return 0;
	}

	int sb(int rs, int rt, int immediate){
		return 0;
	}

	int lui(int rs, int rt, int immediate){
		return 0;
	}

	int andi(int rt, int rs, int immediate){
	    int ans;
	    ans = reg[rs] & immediate;
	    register_acess(rt, ans, 1);
		return 0;
	}

	int ori(int rt, int rs, int immediate){
	    int ans;
	    ans = reg[rs] | immediate;
	    register_acess(rt, ans, 1);
		return 0;
	}

	int nori(int rt, int rs, int immediate){
	    int ans;
	    ans = ~(reg[rs] | immediate);
	    register_acess(rt, ans, 1);
		return 0;
	}

	int slti(int rt, int rs, int immediate){
	    int ans;
	    ans = reg[rs] < immediate;
	    register_acess(rt, ans, 1);
		return 0;
	}

	int beq(int rs, int rt, int immediate){
	    if(reg[rs] == reg[rt]){
            pc = pc + 4 + immediate * 4;
	    }
		return 0;
	}

	int bne(int rs, int rt, int immediate){
	    if(reg[rs] != reg[rt]){
            pc = pc + 4 + immediate * 4;
	    }
		return 0;
	}

	int bgtz(int rs, int immediate){
	    if(reg[rs] > 0){
            pc = pc + 4 + immediate * 4;
	    }
		return 0;
	}

	int halt_f(void){
		return 0;
	}

    ///
	int one_cycle_simulator(string cmd){
        cmd = 0x3008001A;
        int opcode = cmd >> 26;

    ///R-Type instruction
    if(  opcode == 0x00){
        int rs, rt, rd, shamt, funct;
        rs = cmd << 6 >> 27;
        rt = cmd << 11 >> 27;
        rd = cmd << 16 >> 27;
        shamt = cmd << 21 >> 27;
        funct = cmd << 26 >> 26;

        switch (funct){
        case 0x20:
            add(rs, rt, rd);
            break;

        case 0x21:
            addu(rs, rt, rd);
            break;

        case 0x22:
            sub(rs, rt, rd);
            break;

        case 0x24:
            and_f(rs, rt, rd);
            break;

        case 0x25:
            or_f(rs, rt, rd);
            break;
        ///

        case 0x26:
            xor_f(rs, rt, rd);
            break;

        case 0x27:
            nor_f(rs, rt, rd);
            break;

        case 0x28:
            nand_f(rs, rt, rd);
            break;

        case 0x2A:
            slt(rs, rt, rd);
            break;
        ///


        case 0x00:
            sll(rs, rt, rd);
            break;

        case 0x02:
            srl(rs, rt, rd);
            break;

        case 0x03:
            sra(rs, rt, rd);
            break;

        case 0x08:
            jr(rs, rt, rd);
            break;
        ///

        case 0x18:
            mult(rs, rt, rd);
            break;

        case 0x19:
            multu(rs, rt, rd);
            break;

        case 0x10:
            mfhi(rs, rt, rd);
            break;

        case 0x12:
            mflo(rs, rt, rd);
            break;

        //default:
        }
    }
    /// J-Type instruction
    else if(  opcode == 0x02 || opcode == 0x03){
        int address;

        address= cmd << 6 >> 6;
        if(opcode == 0x02){
            jump(address);
        }else{
            jal(address);
        }
    }else if(opcode == 0x3f){
        halt_f();
    }
    ///I-Type instruction
    else{

        int rs, rt, immediate;
        rs = cmd << 6 >> 27;
        rt = cmd << 11 >> 27;
        immediate = cmd << 16 >> 16;


        switch (opcode){
        case 0x08:
            addi(rs, rt, immediate);
            break;

        case 0x09:
            addiu(rs, rt, immediate);
            break;

        case 0x23:
            slw(rs, rt, immediate);
            break;

        case 0x21:
            lh(rs, rt, immediate);
            break;

        case 0x25:
            lhu(rs, rt, immediate);
            break;
        ///

        case 0x20:
            lb(rs, rt, immediate);
            break;

        case 0x24:
            lbu(rs, rt, immediate);
            break;

        case 0x2B:
            sw(rs, rt, immediate);
            break;

        case 0x29:
            sh(rs, rt, immediate);
            break;
        ///


        case 0x28:
            sb(rs, rt, immediate);
            break;

        case 0x0F:
            lui(rs, rt, immediate);
            break;

        case 0x0C:
            addi(rs, rt, immediate);
            break;

        case 0x0D:
            ori(rs, rt, immediate);
            break;
        ///

        case 0x0E:
            nori(rs, rt, immediate);
            break;

        case 0x0A:
            slti(rs, rt, immediate);;
            break;

        case 0x04:
            beq(rs, rt, immediate);
            break;

        case 0x05:
            bne(rs, rt, immediate);
            break;

        case 0x07:
            bgtz(rs, rt, immediate);
            break;

        //default:
        }
        return 0;
    }

    }



int main(){

    ///input
    pc = 0x00000000;
    num_iimage = 0x0000000D;
    int iimage[13] = {0x30080000,
                    0x30090000,
                    0x292A0003,
                    0x11400003,
                    0x01094020,

                    0x21290001,
                    0x08000002,
                    0xAC080000,
                    0xFFFFFFFF,
                    0xFFFFFFFF,

                    0xFFFFFFFF,
                    0xFFFFFFFF,
                    0xFFFFFFFF};

    for(int i = 0; i < num_iimage; i++){
        imemory[i] = iimage[i];
    }

    sp = 0x00000400;
    num_iimage = 0x00000003;
    int iimage[3] ={0x12345678,
                    0x9ABCDEF0,
                    0x13572468};

    for(int i = 0; i < num_dimage; i++){
        imemory[i] = dimage[i];


    ///cin >> hex >> cmd;

    cmd << 32-6 >> 32-6;
    ///cout << hex << (cmd << 32-6 >> 32-6) << endl;


    do{
        one_cycle_simulator(cmd);
    }while(!quit_flag);


    ///n = -1;
    ///cout << bitset<32>(n) << endl;
    if((cmd << 32-6 >> 32-6) == 0x1a)
        cout << "Hello world!" << endl;
    return 0;
}
