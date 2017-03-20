#include "instrctions.h"
#include "io.h"

    // instruction functions
    int add(int rd, int rs, int rt){
        int ans = reg[rs] + reg[rt];
        register_acess(rd, ans, 1);
        overflow_f(ans, reg[rs], reg[rt]);
		return 0;
	}

	int addu(int rd, int rs, int rt){
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
	    ///error detection of write register zero is prior to other error detections
	    if(rt == 0){
            register_acess(rt, 0, 1);
	    }

	    tmp = dmemory_acess(reg[rs] + immediate, 0, 4, 0);
	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int lh(int rt, int rs, int immediate){
	    int tmp, address;
	    if(rt == 0){
            register_acess(rt, 0, 1);
	    }

	    address = reg[rs] + immediate;
	    tmp = dmemory_acess(address, 0, 2, 0);
	    tmp = tmp << 16 >> 16;
	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int lhu(int rt, int rs, int immediate){
	    int tmp, address;
	    if(rt == 0){
            register_acess(rt, 0, 1);
	    }

	    address = reg[rs] + immediate;
	    tmp = dmemory_acess(address, 0, 2, 0);
	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int lb(int rt, int rs, int immediate){
	    int tmp, address;
	    if(rt == 0){
            register_acess(rt, 0, 1);
	    }

	    address = reg[rs] + immediate;
	    tmp = dmemory_acess(address, 0, 1, 0);
	    tmp = tmp << 24 >> 24;
	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int lbu(int rt, int rs, int immediate){
	    int tmp, address;
	    if(rt == 0){
            register_acess(rt, 0, 1);
	    }

	    address = reg[rs] + immediate;
	    tmp = dmemory_acess(address, 0, 1, 0);

	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int sw(int rt, int rs, int immediate){
	    int tmp, address;
	    if(rt == 0){
            register_acess(rt, 0, 1);
	    }

	    address = reg[rs] + immediate;
	    tmp = dmemory_acess(address, 0, 4, 0);

	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int sh(int rt, int rs, int immediate){
	    int tmp, address;
	    if(rt == 0){
            register_acess(rt, 0, 1);
	    }

	    address = reg[rs] + immediate;
	    tmp = dmemory_acess(address, 0, 2, 0);
	    tmp = tmp & 0x0000FFFF;
	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int sb(int rt, int rs, int immediate){
	    int tmp, address;
	    if(rt == 0){
            register_acess(rt, 0, 1);
	    }

	    address = reg[rs] + immediate;
	    tmp = dmemory_acess(address, 0, 1, 0);
	    tmp = tmp & 0x000000FF;
	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int lui(int rt, int immediate){
	    int tmp;
	    tmp = immediate << 16;
	    register_acess(rt, tmp, 1);
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

	///

	int beq(int rs, int rt, int immediate){
	    if(reg[rs] == reg[rt]){
            pc = pc + 4 + immediate * 4;
            pc_changed = true;
	    }
		return 0;
	}

	int bne(int rs, int rt, int immediate){
	    if(reg[rs] != reg[rt]){
            pc_access(pc + 4 + immediate * 4, 1);
	    }
		return 0;
	}

	int bgtz(int rs, int immediate){
	    if(reg[rs] > 0){
            pc_access(pc + 4 + immediate * 4, 1);
	    }
		return 0;
	}

	int jr(int rs){
	    pc_access(reg[rs], 1);
		return 0;
	}

	int mult(int rs, int rt){
	    if(mul_flag){
             fprintf(error_dump , "In cycle %d: Overwrite HI-LO registers\n", cycle);
             //printf("In cycle %d: Overwrite HI-LO registers\n", cycle);
	    }
	    mul_flag = true;
	    hi_access( (int)( ((long long)reg[rs] * (long long)reg[rt]) >> 32)      , 1);
        lo_access( (int)( ((long long)reg[rs] * (long long)reg[rt]) << 32 >> 32), 1);
        return 0;
	}

	int multu(int rs, int rt){
	    if(mul_flag){
             fprintf(error_dump , "In cycle %d: Overwrite HI-LO registers\n", cycle);
             //printf("In cycle %d: Overwrite HI-LO registers\n", cycle);
	    }
	    mul_flag = true;
	    hi_access( (unsigned int)( ((unsigned long long)reg[rs] * (unsigned long long)reg[rt]) >> 32) , 1);
        lo_access( (unsigned int)( ((unsigned long long)reg[rs] * (unsigned long long)reg[rt]) << 32 >> 32), 1 );
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
	    pc_access(address ,1);
		return 0;
	}

	int jal(int address){
	    register_acess(31, pc+4, 1);
	    pc_access(address, 1);
		return 0;
	}

	int halt_f(void){
	    quit_flag = true;
		return 0;
	}
