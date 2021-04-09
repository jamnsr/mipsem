#include "controller.h"
#include "view.h"

void initializeModelVariables(Controller* this){
    this->mips32.PC = 0;

    this->mips32.ALU_add_count = 0;
    this->mips32.ALU_sub_count = 0;
    this->mips32.ALU_and_count = 0;
    this->mips32.ALU_or_count = 0;
    this->mips32.ALU_slt_count = 0;

    this->mips32.mem_reads = 0;
    this->mips32.mem_writes = 0;

    /* Just Some Random Tests */
    this->mips32.registers[17] = -6; //s1
    this->mips32.registers[16] = 4; //s0
}
void initializeInst_Mem(Controller* this, char* fname){
    FILE* fptr = fopen(fname,"rb");
    // Determine size of input (instruction memory) in bytes
    fseek(fptr, 0, SEEK_END);
    uint32_t num_instr = (uint32_t)(ftell(fptr) / 4);
    rewind(fptr);
    // Allocate memory and read into it from binary file
    // +1 for terminating instruction = 0
    this->mips32.instr_mem = malloc((num_instr + 1) * sizeof(uint32_t));
    this->mips32.instr_mem[num_instr] = 0;
    fread(this->mips32.instr_mem, sizeof(uint32_t), num_instr, fptr);
    fclose(fptr);
}
void initializeMemory(Controller* this, char* fname){
    FILE* fptr = fopen(fname,"rb");
    // Determine size of input (data memory) in bytes
    fseek(fptr, 0, SEEK_END);
    this->mips32.mem_words = (int)(ftell(fptr) / 4);
    rewind(fptr);
    // Allocate memory and read into it from binary file
    this->mips32.data_mem = malloc(this->mips32.mem_words * sizeof(uint32_t));
    fread(this->mips32.data_mem, sizeof(uint32_t), this->mips32.mem_words, fptr);
    fclose(fptr);
}
void controllerExecuteSimulation(Controller* this, char* inst_file, char* mem_file){

    initializeModelVariables(this);
    initializeInst_Mem(this, inst_file);
    initializeMemory(this, mem_file);

    this->num_cycles = 0;

    uint32_t inst = modelFetchInstruction(&this->mips32);
    while( inst ){
        uint32_t opcode = inst >> 26;
        if(opcode == RTYPE){
            execRTYPE(&this->mips32, inst);
        }
        else if(opcode == LW || opcode == SW){
            execITYPE(&this->mips32, inst);
        }
        else if(opcode == BEQ){
            execBRANCH(&this->mips32, inst);
        }
        else if(opcode == JMP){
            execJUMP(&this->mips32, inst);
        }

        this->num_cycles++;

        printScoreboard(this);

        inst = modelFetchInstruction(&this->mips32);
    }
}