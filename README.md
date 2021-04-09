# Part A

The python file 'partA.py' implements a basic MIPS32 assembler.
Usage: `python partA.py <instructions.asm>` 

This will output a raw binary file that encodes each instruction provided in the .asm file.

# Part B

This C project implements a simple MIPS32 simulator.
Usage:

`make` 
`./smolmips <encoded.bin> <memory.bin>`
`make clean` (If Needed)

**Note both input files' byte ordering is in little-endian.**

This will run the simulator and print the associated 'scoreboard' at the end of each clock cycle.

Test input files included.