#include "instrctions.h"
#include "io.h"
#include <stdint.h>
    // instruction functions
    int add(int rd, int rs, int rt){
        int ans = reg[rs] + reg[rt];
        //of_tmp is the temporary variable to detect overflow error
        int of_tmp1, of_tmp2;
        of_tmp1 = reg[rs];
        of_tmp2 = reg[rt];

        register_acess(rd, ans, 1);
        overflow_f(of_tmp1, of_tmp2, 1);
		return 0;
	}

	int addu(int rd, int rs, int rt){
        //unsigned int ans;
        int ans;
        //ans = (unsigned)reg[rs] + (unsigned)reg[rt];
        ans = reg[rs] + reg[rt];
        register_acess(rd, ans, 1);
		return 0;
	}

	int sub(int rd, int rs, int rt){
	    int of_tmp1, of_tmp2;
        of_tmp1 = reg[rs];
        of_tmp2 = -reg[rt];

        int ans = reg[rs] - reg[rt];
        register_acess(rd, ans, 1);
        overflow_f(of_tmp1, of_tmp2, 1);
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
	    int of_tmp1, of_tmp2;
        of_tmp1 = reg[rs];
        of_tmp2 = immediate;

        register_acess(rt, ans, 1);
        overflow_f(of_tmp1, of_tmp2, 1);
		return 0;
	}

	int addiu(int rt, int rs, int immediate){
		int ans;
        //ans = reg[rs]  + (((unsigned int)immediate)&0x0000FFFF);???
        ans = reg[rs]  + immediate;
        register_acess(rt, ans, 1);
		return 0;
	}

	int andi(int rt, int rs, int immediate){
	    int ans;
	    ans = reg[rs] & (((unsigned int)immediate)&0x0000FFFF);///???
	    register_acess(rt, ans, 1);
		return 0;
	}

	int ori(int rt, int rs, int immediate){
	    int ans;
	    ans = reg[rs] | (((unsigned int)immediate)&0x0000FFFF);
	    register_acess(rt, ans, 1);
		return 0;
	}

	int nori(int rt, int rs, int immediate){
	    int ans;
	    ans = ~(reg[rs] | (((unsigned int)immediate)&0x0000FFFF));
	    register_acess(rt, ans, 1);
		return 0;
	}

	int slti(int rt, int rs, int immediate){
	    int ans;
	    ans = reg[rs] < immediate;
	    register_acess(rt, ans, 1);
		return 0;
	}


	//memory access instructions


	int lw(int rt, int rs, int immediate){
	    int tmp;
	    ///error detection of write register zero is prior to other error detections
	    if(rt == 0){
            register_acess(rt, 0, 1);
	    }
	    overflow_f(reg[rs], immediate, 1);
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
	    overflow_f(reg[rs], immediate, 1);

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

	    overflow_f(reg[rs], immediate, 1);
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
	    overflow_f(reg[rs], immediate, 1);

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
	    overflow_f(reg[rs], immediate, 1);

	    address = reg[rs] + immediate;
	    tmp = dmemory_acess(address, 0, 1, 0);

	    if(rt != 0){
            register_acess(rt, tmp, 1);
	    }
		return 0;
	}

	int sw(int rt, int rs, int immediate){
	    int tmp, address;

	    tmp = reg[rt];
	    overflow_f(reg[rs], immediate, 1);
	    address = reg[rs] + immediate;
	    dmemory_acess(address, tmp, 4, 1);

		return 0;
	}

	int sh(int rt, int rs, int immediate){
	    int tmp, address;

	    tmp = reg[rt];
	    tmp = tmp & 0x0000FFFF;
	    overflow_f(reg[rs], immediate, 1);
	    address = reg[rs] + immediate;
	    dmemory_acess(address, tmp, 2, 1);

		return 0;
	}

	int sb(int rt, int rs, int immediate){
	    int tmp, address;

	    tmp = reg[rt];
	    tmp = tmp & 0x000000FF;
	    overflow_f(reg[rs], immediate, 1);
	    address = reg[rs] + immediate;
	    dmemory_acess(address, tmp, 1, 1);

		return 0;
	}

	int lui(int rt, int immediate){
	    int tmp;
	    tmp = immediate << 16;
	    register_acess(rt, tmp, 1);
		return 0;
	}


	///
	int mult(int rs, int rt){
	    if(mul_flag){
             fprintf(error_dump , "In cycle %d: Overwrite HI-LO registers\n", cycle);
             //printf("In cycle %d: Overwrite HI-LO registers\n", cycle);
	    }
	    mul_flag = true;
	    long long ans = reg[rs] * reg[rt];
	    hi_access( (int)(ans >> 32) , 1);
	    lo_access( (int)(ans << 32 >> 32) , 1);
	    //std::cout << "ans: " << ans << "\n";
	    //printf("hi %d\n",(int)(ans << 32 >> 64));
	    //printf("lo %d\n", (int)(ans >> 32));
	    //hi_access( (int)( (((long long)reg[rs]) * ((long long)reg[rt])) >> 32)      , 1);
        //lo_access( (int)( (((long long)reg[rs]) * ((long long)reg[rt]) << 32 >> 32), 1);
        return 0;
	}

	int multu(int rs, int rt){
	    if(mul_flag){
             fprintf(error_dump , "In cycle %d: Overwrite HI-LO registers\n", cycle);
             //printf("In cycle %d: Overwrite HI-LO registers\n", cycle);
	    }
	    mul_flag = true;
	    int64_t a,b,c,d;
        int e,f;
        a = (unsigned int)reg[rs];
        //std::cout << "hi: " << std::bitset<64>(a) << "\n";
        //std::cout << "lo: " << std::bitset<64>(b) << "\n";
        b = (unsigned int)reg[rt];
        c = ((int64_t)( a * b)) >> 32;
        d = ((int64_t)( a * b)) << 32 >> 32;
        e = c;
        f = d;
        //std::cout << "hi: " << std::bitset<32>(e) << "\n";
        //std::cout << "lo: " << std::bitset<32>(f) << "\n";

	    hi_access(e,1);
	    lo_access(f,1);
	    //hi_access( (unsigned int)( ((unsigned long long)reg[rs] * (unsigned long long)reg[rt]) >> 32) , 1);
        //lo_access( (unsigned int)( ((unsigned long long)reg[rs] * (unsigned long long)reg[rt]) << 32 >> 32), 1 );
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

	///

	int beq(int rs, int rt, int immediate){
	    if(reg[rs] == reg[rt]){
            overflow_f(pc, immediate << 2, 1);
            pc_access(pc + (immediate << 2), 1);
	    }
		return 0;
	}

	int bne(int rs, int rt, int immediate){
	    if(reg[rs] != reg[rt]){
            overflow_f(pc, immediate << 2, 1);
            pc_access(pc + (immediate << 2), 1);
	    }
		return 0;
	}

	int bgtz(int rs, int immediate){
	    if(reg[rs] > 0){
            overflow_f(pc, immediate << 2, 1);
            pc_access(pc + (immediate << 2), 1);
	    }
		return 0;
	}


	int jump(unsigned int address){
	    unsigned int tmp;
	    tmp = pc >> 28 << 28;
	    tmp = tmp | (address << 2);
	    pc_access(tmp ,1);
		return 0;
	}

	int jal(unsigned int address){
	    register_acess(31, pc, 1);
	    unsigned int tmp;
	    tmp = pc >> 28 << 28;
	    tmp = tmp | (address << 2);
	    pc_access(tmp ,1);
		return 0;
	}

	int jr(int rs){
	    pc_access(reg[rs], 1);
		return 0;
	}

	int halt_f(void){
	    quit_flag = true;
		return 0;
	}
