/*
    Jamal Nasser
    CPSC 3300
    Project 2 - Part B
    
    Usage:  ./smolmips <instructions.bin> <memory.bin>
    See README for more details
*/

#include "controller.h"

int main(int argc, char* argv[]){
    // Registers are simply an array of 32 words
    // Instruction memory is malloc'd for using the first input file
    // Data memory is malloc'd for using the second input file
    Controller ctrl;
    controllerExecuteSimulation(&ctrl, argv[1], argv[2]);
    return 0;
}