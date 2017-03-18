#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main()
{
    int cmd, opcode;
    int imemory[127] = {0};
    int dmemory[127] = {0};
    int reg[31] = {0};

    int dmemory_write(int address, int value){
        dmemory[address/4] = value;
        return 0;
    }

    int dmemory_read(int address){
        return dmemory[address / 4];
    }

    {/// instruction functions

        ///overflow problem needs to-be-done
    	int add(int rs, int rt, int rd){
        reg[rd] = reg[rs] + reg[rt];
		return 0;
	}

	int addu(int rs, int rt, int rd){
        unsigned int ans;
        ans = (unsigned)reg[rs] + (unsigned)reg[rt];
        reg[rd] = (int)ans;
		return 0;
	}

	int sub(int rs, int rt, int rd){
	    reg[rd] = reg[rs] - reg[rt];
		return 0;
	}

	int and(int rs, int rt, int rd){
	    reg[rd] = reg[rs] & reg[rt];
		return 0;
	}

	int or(int rs, int rt, int rd){
	    reg[rd] = reg[rs] | reg[rt];
		return 0;
	}

	int xor(int rs, int rt, int rd){
	    reg[rd] = reg[rs] ^ reg[rt];
		return 0;
	}

	int nor(int rs, int rt, int rd){
	    reg[rd] = ~(reg[rs] | reg[rt]);
		return 0;
	}

	int nand(int rs, int rt, int rd){
	    reg[rd] = ~(reg[rs] & reg[rt]);
		return 0;
	}

	int slt(int rs, int rt, int rd){
	    if(reg[rs] < reg[rt])
            reg[rd] = 1;
        else
            reg[rd] = 0;
		return 0;
	}

	int sll(int rs, int rt, int rd){
	    reg[rd] = reg[rd] << reg[rt];
		return 0;
	}

	int srl(int rs, int rt, int rd){
	    reg[rd] = (unsigned int)reg[rd] >> reg[rt];
		return 0;
	}

	int sra(int rs, int rt, int rd){
	    reg[rd] = reg[rd] >> reg[rt];
		return 0;
	}

	int jr(int rs, int rt, int rd){
		return 0;
	}

	int mult(int rs, int rt, int rd){
		return 0;
	}

	int multu(int rs, int rt, int rd){
		return 0;
	}

	int mfhi(int rs, int rt, int rd){
		return 0;
	}

	int mflo(int rs, int rt, int rd){
		return 0;
	}

	int jump(int address){
		return 0;
	}

	int jal(int address){
		return 0;
	}

	int halt(v){
		return 0;
	}

	int addi(int rs, int rt, int immediate){
		return 0;
	}

	int addiu(int rs, int rt, int immediate){
		return 0;
	}

	int slw(int rs, int rt, int immediate){
		return 0;
	}

	int lh(int rs, int rt, int immediate){
		return 0;
	}

	int lhu(int rs, int rt, int immediate){
		return 0;
	}

	int lb(int rs, int rt, int immediate){
		return 0;
	}

	int lbu(int rs, int rt, int immediate){
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

	int addi(int rs, int rt, int immediate){
		return 0;
	}

	int ori(int rs, int rt, int immediate){
		return 0;
	}

	int nori(int rs, int rt, int immediate){
		return 0;
	}

	int slti(int rs, int rt, int immediate){
		return 0;
	}

	int beq(int rs, int rt, int immediate){
		return 0;
	}

	int bne(int rs, int rt, int immediate){
		return 0;
	}

	int bgtz(int rs, int rt, int immediate){
		return 0;
	}



    }




    ///cin >> hex >> cmd;
    cmd = 0x3008001A;
    opcode = cmd >> 26;

    ///R-Type instruction
    if(  opcode == 0x00){
        int rs, rt, rd, shamt, funct;
        rs = cmd << 6 >> 27;
        rt = cmd << 11 >> 27;
        rd = cmd << 16 >> 27;
        shamt = cmd << 21 >> 27;
        funct = cmd << 26 >> 26;

        switch (funct):
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
            and(rs, rt, rd);
            break;

        case 0x25:
            or(rs, rt, rd);
            break;
        ///

        case 0x26:
            xor(rs, rt, rd);
            break;

        case 0x27:
            nor(rs, rt, rd);
            break;

        case 0x28:
            nand(rs, rt, rd);
            break;

        case 0x2A:
            slt(rs, rt, rd);
            break;
        ///


        case 0x00:
            sll(ss, rt, rd);
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

        default:
            break;


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
        halt();
    }
    ///I-Type instruction
    else{

        int rs, rt, immediate;
        rs = cmd << 6 >> 27;
        rt = cmd << 11 >> 27;
        immediate = cmd << 16 >> 16;


        switch (opcode):
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

        default:
            break;
    }





    cmd << 32-6 >> 32-6;
    ///cout << hex << (cmd << 32-6 >> 32-6) << endl;


    ///n = -1;
    ///cout << bitset<32>(n) << endl;
    if((cmd << 32-6 >> 32-6) == 0x1a)
        cout << "Hello world!" << endl;
    return 0;
}
