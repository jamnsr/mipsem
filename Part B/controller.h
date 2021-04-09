#pragma once
#include "model.h"

typedef struct {
    Model mips32;
    int num_cycles;
} Controller;

void initializeModelVariables(Controller* this);
void initializeInst_Mem(Controller* this, char* fname);
void initializeMemory(Controller* this, char* fname);

void controllerExecuteSimulation(Controller* this, char* inst_file, char* mem_file);