'''

Jamal Nasser
CPSC 3300 
Project 2 Part A

'''

import re

# Converts register names to binary literals
def getBits(r):
  if r == 'zero':
    return '00000'
  elif r == 'at':
    return '00001'
  elif r == 'v0':
    return '00010'
  elif r == 'v1':
    return '00011'
  elif r == 'a0':
    return '00100'
  elif r == 'a1':
    return '00101'
  elif r == 'a2':
    return '00110'
  elif r == 'a3':
    return '00111'
  elif r == 't0':
    return '01000'
  elif r == 't1':
    return '01001'
  elif r == 't2':
    return '01010'
  elif r == 't3':
    return '01011'
  elif r == 't4':
    return '01100'
  elif r == 't5':
    return '01101'
  elif r == 't6':
    return '01110'
  elif r == 't7':
    return '01111'
  elif r == 's0':
    return '10000'
  elif r == 's1':
    return '10001'
  elif r == 's2':
    return '10010'
  elif r == 's3':
    return '10011'
  elif r == 's4':
    return '10100'
  elif r == 's5':
    return '10101'
  elif r == 's6':
    return '10110'
  elif r == 's7':
    return '10111'
  elif r == 't8':
    return '11000'
  elif r == 't9':
    return '11001'
  elif r == 'k0':
    return '11010'
  elif r == 'k1':
    return '11011'
  elif r == 'gp':
    return '11100'
  elif r == 'sp':
    return '11101'
  elif r == 'fp':
    return '11110'
  elif r == 'ra':
    return '11111'
# Creates the 32 bit binary literal for an instruction
def encode(inst):

  encoded = format(0, '032b')

  #Preprocess input
  inst = inst.lower().replace(')','').replace('(',' ').replace('$','').rstrip()
  inst = re.split(', |' ' ', inst)

  # R Type Instruction
  '''
  inst[0] = Instruction Name
  inst[1] = Rd
  inst[2] = Rs
  inst[3] = Rt
  '''
  if inst[0] == 'add' or inst[0] == 'sub' or inst[0] == 'and' or inst[0] == 'or' or inst[0] == 'slt':
    op = '000000'
    shamt = '00000'
    funct = '000000'

    rd = getBits(inst[1])
    rs = getBits(inst[2])
    rt = getBits(inst[3])
    
    if inst[0] == 'add':
      funct = '100000'
    elif inst[0] == 'sub':
      funct = '100010'    
    elif inst[0] == 'and':
      funct = '100100'
    elif inst[0] == 'or':
      funct = '100101'
    elif inst[0] == 'slt':
      funct = '101010'
    
    encoded = op + rs + rt + rd + shamt + funct

  # Memory Reference Instruction
  '''
  inst[0] = Instruction Name
  inst[1] = Rt
  inst[2] = Offset
  inst[3] = Rs
  '''
  if inst[0] == 'lw' or inst[0] == 'sw':
    op = '100011' if inst[0] == 'lw' else '101011'
    rs = getBits(inst[3])
    rt = getBits(inst[1])
    adrs = format( int(inst[2], 16) , '016b' )

    encoded = op + rs + rt + adrs

  # Beq Instruction
  '''
  inst[0] = Instruction Name
  inst[1] = Rs
  inst[2] = Rt
  inst[3] = Offset
  '''
  if inst[0] == 'beq':
    op = '000100'
    rs = getBits(inst[1])
    rt = getBits(inst[2])
    adrs = format( int(inst[3], 16) , '016b' )

    encoded = op + rs + rt + adrs

  # Jump Instruction
  '''
  inst[0] = Instruction Name
  inst[1] = Target
  '''
  if inst[0] == 'j':
    op = '000010'
    adrs = format( int(inst[1], 16) , '026b' )

    encoded = op + adrs
  
  return encoded
# Converts 32 bit binary literal to raw bytes
def stringToBytes(s):
    num = int(s, 2)
    b = bytearray()
    while num:
        b.append(num & 0xff)
        num >>= 8
    return bytes(b)



#Open input file
inFile = open("input.asm")

#Open output file
outFile = open("encoded.bin", "wb")

for instruction in inFile:
  binaryString = encode(instruction)
  print(hex(int(binaryString, 2)))
  print(binaryString)
  print("--------------")
  outFile.write(stringToBytes(binaryString))


