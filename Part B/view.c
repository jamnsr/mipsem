#include "view.h"

void printScoreboard(Controller* this){
    printf("\n\n==========================\n");
    printf("//////////////////////////\n");
    printf("==========================\n\n");

    printf("TOTAL CYCLES: %d\n", this->num_cycles);

    printf("---------------------\n");
    printf("MEMORY READS: %d\n", this->mips32.mem_reads);
    printf("MEMORY WRITES: %d\n", this->mips32.mem_writes);

    printf("---------------------\n");
    printf("ALU OPERATION STATS:\n");
    printf("---------------------\n");
    printf("ADD: %d\n", this->mips32.ALU_add_count);
    printf("SUB: %d\n", this->mips32.ALU_sub_count);
    printf("AND: %d\n", this->mips32.ALU_and_count);
    printf("OR: %d\n", this->mips32.ALU_or_count);
    printf("SLT: %d\n", this->mips32.ALU_slt_count);

    printf("---------------------\n");
    printf("PC (at end of cycle): %#08x\n", (uint32_t)this->mips32.PC);

    printf("---------------------\n");
    printf("REGISTER CONTENT:\n");
    printf("---------------------\n");
    for(int i = 0; i < NUM_REGS; i++){
        printf("R%d: %d\n", i, this->mips32.registers[i]);
    }

    printf("---------------------\n");
    printf("DATA MEMORY CONTENT:\n");
    printf("---------------------\n");
    for(int i = 0; i < this->mips32.mem_words; i++){
        printf("WORD %d: %d\n", i, this->mips32.data_mem[i]);
    }

}