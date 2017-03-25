#include "one_cycle_simulator.h"
#include "instrctions.h"
#include "io.h"



int one_cycle_simulator(int cmd){

    int opcode = ((unsigned int)cmd) >> 26;

    ///R-Type instruction
    if(  opcode == 0x00){
        int rs, rt, rd, shamt, funct;
        rs = ((unsigned int)cmd) << 6 >> 27;
        rt = ((unsigned int)cmd) << 11 >> 27;
        rd = ((unsigned int)cmd) << 16 >> 27;
        shamt = ((unsigned int)cmd) << 21 >> 27;
        funct = ((unsigned int)cmd) << 26 >> 26;
        //if(cycle == 92 || cycle == 94){
          //  std::cout << "cycle " << cycle << ": \n";
           // std::cout << "reg[1]: " << reg[1] << "  reg[2]: " << reg[2] << "\n\n";
        //}

        switch (funct){
        case 0x20:
            add(rd, rs, rt);
            break;

        case 0x21:
            addu(rd, rs, rt);
            break;

        case 0x22:
            sub(rd, rs, rt);
            break;

        case 0x24:
            and_f(rd, rs, rt);
            break;

        case 0x25:
            or_f(rd, rs, rt);
            break;
        ///

        case 0x26:
            xor_f(rd, rs, rt);
            break;

        case 0x27:
            nor_f(rd, rs, rt);
            break;

        case 0x28:
            nand_f(rd, rs, rt);
            break;

        case 0x2A:
            slt(rd, rs, rt);
            break;
        ///


        case 0x00:
            if( rt || rd || shamt){
                sll(rd, rt, shamt);
            }

            break;

        case 0x02:
            srl(rd, rt, shamt);
            break;

        case 0x03:
            sra(rd, rt, shamt);
            break;

        case 0x08:
            jr(rs);
            break;
        ///

        case 0x18:
            mult(rs, rt);
            break;

        case 0x19:
            multu(rs, rt);
            break;

        case 0x10:
            mfhi(rd);
            break;

        case 0x12:
            mflo(rd);
            break;

        default:
            printf("illegal instruction found at 0x%08X\n", pc - 4);
            quit_flag = true;
            return 0;

        }
    }
    /// J-Type instruction
    else if(  opcode == 0x02 || opcode == 0x03){
        int address;

        address= ((unsigned int)cmd) << 6 >> 6;
        if(opcode == 0x02){
            jump( ((unsigned int)address) );
        }else{
            jal(address);
        }
    }else if(opcode == 0x3f){
        halt_f();
    }
    ///I-Type instruction
    else if(opcode == 0x4 || opcode == 0x5 || (opcode >= 0x7 && opcode <= 0xA) ||
            opcode == 0x28 || opcode == 0x29 || (opcode >= 0xC && opcode <= 0xF) ||
            opcode == 0x20 || opcode == 0x21 || opcode == 0x2B || (opcode >= 0x23 && opcode <= 0x25) )
    {
        int rs, rt, immediate;
        rs = ((unsigned int)cmd) << 6 >> 27;
        rt = ((unsigned int)cmd) << 11 >> 27;
        immediate = (cmd) << 16 >> 16;

        switch (opcode){
        case 0x08:
            addi(rt, rs, immediate);
            break;

        case 0x09:
            addiu(rt, rs, immediate);
            break;

        case 0x23:
            lw(rt, rs, immediate);
            break;

        case 0x21:
            lh(rt, rs, immediate);
            break;

        case 0x25:
            lhu(rt, rs, immediate);
            break;
        ///

        case 0x20:
            lb(rt, rs, immediate);
            break;

        case 0x24:
            lbu(rt, rs, immediate);
            break;

        case 0x2B:
            sw(rt, rs, immediate);
            break;

        case 0x29:
            sh(rt, rs, immediate);
            break;
        ///


        case 0x28:
            sb(rt, rs, immediate);
            break;

        case 0x0F:
            lui(rt, immediate);
            break;

        case 0x0C:
            addi(rt, rs, immediate);
            break;

        case 0x0D:
            ori(rt, rs, immediate);
            break;
        ///

        case 0x0E:
            nori(rt, rs, immediate);
            break;

        case 0x0A:
            slti(rt, rs, immediate);;
            break;

        case 0x04:
            beq(rt, rs, immediate);
            break;

        case 0x05:
            bne(rt, rs, immediate);
            break;

        case 0x07:
            bgtz(rs, immediate);
            break;

        //default:
        }
    }else{
            printf("illegal instruction found at 0x%08X\n", pc - 4);
            quit_flag = true;
        }
        return 0;


    }

