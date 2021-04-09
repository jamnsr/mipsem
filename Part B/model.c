#include "model.h"

// Program Counter
uint32_t modelFetchInstruction(Model* this){
    return this->instr_mem[this->PC / sizeof(uint32_t)];
}

// Register File
int32_t modelReadReg(Model* this, uint32_t reg){
    return this->registers[reg];
}
void modelWriteReg(Model* this, uint32_t reg, int32_t data){
    this->registers[reg] = data;
}

// Data Memory
int32_t modelReadDataMem(Model* this, uint32_t address){
    this->mem_reads++;
    return *(this->data_mem + (address / sizeof(address)));
}
void modelWriteDataMem(Model* this, uint32_t address, int32_t data){
    this->mem_writes++;
    *(this->data_mem + (address / sizeof(address))) = data;
}

// ALU
int32_t modelALU_op(Model* this, int32_t first, int32_t second, uint32_t control){
    //ADD
    if(control == 0x2){
        this->ALU_add_count++;
        return first + second;
    }
    //SUB
    else if(control == 0x6){
        this->ALU_sub_count++;
        return first - second;
    }
    //AND
    else if(control == 0x0){
        this->ALU_and_count++;
        return first & second;
    }
    //OR
    else if(control == 0x1){
        this->ALU_or_count++;
        return first | second;
    }
    //SLT
    else if(control == 0x7){
        this->ALU_slt_count++;
        return first < second ? 1 : 0;
    }
}

// Execution of different types of instructions
void execRTYPE(Model* this, uint32_t instr){
    // Mask out fields from instruction bits
    uint32_t rs    = (instr & RS_MASK) >> 21;
    uint32_t rt    = (instr & RT_MASK) >> 16;
    uint32_t rd    = (instr & RD_MASK) >> 11;
    uint32_t funct = (instr & FUNCT_MASK);
    // Read values from rs and rt
    int32_t rsVal = modelReadReg(this, rs);
    int32_t rtVal = modelReadReg(this, rt);
    // Execute associated ALU Op
    uint32_t aluOp = 0;
    if(funct == 32)
        aluOp = 0x2;
    else if(funct == 34)
        aluOp = 0x6;
    else if(funct == 36)
        aluOp = 0x0;
    else if(funct == 41)
        aluOp = 0x1;
    else if(funct == 50)
        aluOp = 0x7;
    int32_t aluResult = modelALU_op(this, rsVal, rtVal, aluOp);
    modelWriteReg(this, rd, aluResult);
    this->PC += 4;
}
void execITYPE(Model* this, uint32_t instr){
    // Mask out fields from instruction bits
    uint32_t rs    = (instr & RS_MASK) >> 21;
    uint32_t rt    = (instr & RT_MASK) >> 16;
    int16_t adrs   = (instr & ADRS_MASK);
    // Read register rs
    int32_t rsVal = modelReadReg(this, rs);
    // Sign extend address
    // signExtend(&adrs);
    int32_t signExtended = (int32_t)adrs;
    // Pass into ALU
    uint32_t aluResult = (uint32_t)modelALU_op(this, rsVal, signExtended, 0x2);
    // LW
    if((instr >> 26) == LW){
        int32_t loadedWord = modelReadDataMem(this, aluResult);
        modelWriteReg(this, rt, loadedWord);
    }
    // SW
    else if((instr >> 26) == SW){
        int32_t rtVal = modelReadReg(this, rt);
        modelWriteDataMem(this, aluResult, rtVal);
    }

    this->PC += 4;
}
void execBRANCH(Model* this, uint32_t instr){
    uint32_t rs    = (instr & RS_MASK) >> 21;
    uint32_t rt    = (instr & RT_MASK) >> 16;
    int16_t adrs   = (instr & ADRS_MASK);
    // Read values from rs and rt
    int32_t rsVal = modelReadReg(this, rs);
    int32_t rtVal = modelReadReg(this, rt);
    // Check if zero output from ALU
    int32_t aluResult = modelALU_op(this, rsVal, rtVal, 0x6);
    // signExtend(&adrs);
    if(aluResult == 0){
        int32_t signExtended = (int32_t)adrs;
        signExtended <<= 2;
        this->PC += (signExtended + 4);
    }
    else{
        this->PC += 4;
    }
}
void execJUMP(Model* this, uint32_t instr){
    // Directly setting 28 bits from immediate into PC
    uint32_t imdt = (instr & JMP_MASK) << 2;
    uint32_t upper4PC = this->PC & 0xF0000000;
    this->PC = upper4PC | imdt; 
}
