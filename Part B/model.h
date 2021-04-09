#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define NUM_REGS 32

#define RTYPE 0
#define LW    35
#define SW    43
#define BEQ   4
#define JMP   2

#define RS_MASK    0x3E00000
#define RT_MASK    0x1F0000
#define RD_MASK    0xF800
#define FUNCT_MASK 0x3F
#define ADRS_MASK  0xFFFF
#define JMP_MASK   0x3FFFFFF


typedef struct {
    uint32_t PC;
    uint32_t* instr_mem;
    int32_t registers[NUM_REGS];
    int32_t* data_mem;
    

    int ALU_add_count;
    int ALU_sub_count;
    int ALU_and_count;
    int ALU_or_count;
    int ALU_slt_count;
    
    int mem_words;
    int mem_reads;
    int mem_writes;
} Model;


uint32_t modelFetchInstruction(Model* this);

int32_t modelReadReg(Model* this, uint32_t reg);
void modelWriteReg(Model* this, uint32_t reg, int32_t data);

int32_t modelReadDataMem(Model* this, uint32_t address);
void modelWriteDataMem(Model* this, uint32_t address, int32_t data);


int32_t modelALU_op(Model* this, int32_t first, int32_t second, uint32_t control);

void execRTYPE(Model* this, uint32_t instr);
void execITYPE(Model* this, uint32_t instr);
void execBRANCH(Model* this, uint32_t instr);
void execJUMP(Model* this, uint32_t instr);