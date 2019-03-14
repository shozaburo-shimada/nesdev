#include <stdio.h>
#include "Cpu.h"

typedef struct status_registers{
  uint8_t carry:1;        //bit0
  uint8_t zero:1;         //bit1
  uint8_t interrupt:1;    //bit2
  uint8_t decimal_mode:1; //bit3
  uint8_t break_mode:1;   //bit4
  uint8_t reserve:1;      //bit5
  uint8_t overflow:1;     //bit6
  uint8_t negative:1;     //bit7
}status_registers_t;

typedef struct cpu_registers{
  uint8_t A;    //Accumlator
  uint8_t X;    //Index Register
  uint8_t Y;    //Index Register
  
  union {
    uint8_t sts_byte;
    status_registers_t sts_bits;
  }P;    //Status Regster
  
  //status_registers_t sts_reg;

  uint16_t SP;  //Stack Pointer
  uint16_t PC;  //Program Counter
}cpu_registers_t;

enum Addressing{
  NA_ADDRESSING = 0,
  IMPLIED,
  ACCUMULATOR,
  IMMEDIATE,
  ZERO_PAGE,
  ZERO_PAGE_X,
  XERO_PAGE_Y,
  RELATIVE,
  ABSOLUTE,
  ABSOLUTE_X,
  ABSOLUTE_Y,
  INDIRECT,
  INDIRECT_X,
  INDIRECT_Y
};

enum BaseName{
  NA_BASE_NAME = 0,
  //Load
  LDA, LDX, LDY,  
  //Store
  STA, STX, TAX, TAY, TSX, TXA, TXS, TYA,
  //Calculation
  ADC, AND, ASL, BIT, CMP, CPX, CPY, DEC, DEX, DEY, EOR, INC, INX, INY, LSR, ORA, ROL, ROR, SBC,
  //Stack
  PHA, PHP, PLP, 
  //Jump
  JMP, JSR, RTS, RTI,
  //Branch
  BCC, BCS, BEQ, BMI, BNE, BPL, BVC, BVS,
  //Flag
  CLC, CLD, CLI, CLV, SEC, SED, SEI,
  //Other
  BRK, NOP
};

typedef struct opecode_list{
  BaseName base;
  Addressing add;
  uint8_t cycles;
}opecode_list_t;

opecode_list_t ope_list[]={
  {BRK, IMPLIED, 2}, //0x00
  {ORA, INDIRECT_X, 1}, //0x01
  {NA_BASE_NAME, NA_ADDRESSING, 0}, //0x02
  {NA_BASE_NAME, NA_ADDRESSING, 0}, //0x03
  {NA_BASE_NAME, NA_ADDRESSING, 0}, //0x04
  {ORA, ZERO_PAGE, 2}, //0x05
  {ASL, ZERO_PAGE, 2}, //0x06
  {NA_BASE_NAME, NA_ADDRESSING, 0}, //0x07
  {PHP, IMPLIED, 2}, //0x08
  {ORA, IMMEDIATE, 2}, //0x09
  {ASL, ACCUMULATOR, 1}, //0x0A
  {NA_BASE_NAME, NA_ADDRESSING, 0}, //0x0B
  {NA_BASE_NAME, NA_ADDRESSING, 0}, //0x0C
  {ORA, ABSOLUTE, 1}, //0x0D
  {ASL, ABSOLUTE, 2}, //0x0E
  {NA_BASE_NAME, NA_ADDRESSING, 0}, //0x0F
  {NA_BASE_NAME, NA_ADDRESSING, 0}
};

static cpu_registers_t cpu_reg;

Cpu::Cpu(Cassette *r){
  this->rom = r;
  cpu_reg.PC = 0;

  cpu_reg.P.sts_bits.negative = true;
  cpu_reg.P.sts_bits.overflow = true;
  cpu_reg.P.sts_bits.reserve = false;
  cpu_reg.P.sts_bits.break_mode = true;
  cpu_reg.P.sts_bits.decimal_mode = true;
  cpu_reg.P.sts_bits.interrupt = true;
  cpu_reg.P.sts_bits.zero = true;
  cpu_reg.P.sts_bits.carry = true;
}

void Cpu::init(){
  printf("Cpu::init()\n");
  cpu_reg.PC = 0;
  cpu_reg.P.sts_bits.negative = true;
  cpu_reg.P.sts_bits.overflow = true;
  cpu_reg.P.sts_bits.reserve = false;
  cpu_reg.P.sts_bits.break_mode = true;
  cpu_reg.P.sts_bits.decimal_mode = true;
  cpu_reg.P.sts_bits.interrupt = true;
  cpu_reg.P.sts_bits.zero = true;
  cpu_reg.P.sts_bits.carry = true;
  printf("\tStatus Register: %d\n", getStatusReg());
}

uint8_t Cpu::run(){
  uint8_t cycle = 0;
  printf("Cpu::run()\n");
  printf("Opecode add: %d, Cycle: %d \n", ope_list[0].add, ope_list[0].cycles);
  printf("Opecode add: %d, Cycle: %d \n", ope_list[1].add, ope_list[1].cycles);

  //Fetch Opecode from program rom
  printf("\tprogram counter: %d \n", cpu_reg.PC);
  uint8_t opecode = this->fetch();
  printf("\topecode: %d \n", opecode);

  uint8_t basename = 0;
  uint8_t mode = 0;
  //Fetch Opeland
  uint8_t opeland = this->fetchOpeland(mode);

  //Execute
  this->exec(basename, opeland, mode);

  return cycle;
}

uint8_t Cpu::fetch(){
  printf("Cpu::fetch()\n");
  this->rom->getData(cpu_reg.PC++);
}

uint8_t Cpu::fetchOpeland(uint8_t addressing){
  printf("Cpu::fetchOpeland()\n");
  uint8_t opeland = 0;

  return opeland;
}

void Cpu::exec(uint8_t basename, uint8_t opeland, uint8_t mode){
  printf("Cpu::exec()\n");
}

uint8_t Cpu::getStatusReg(){
  return cpu_reg.P.sts_byte;
}

uint16_t Cpu::getProgramCounter(){
  return cpu_reg.PC;  
}

void Cpu::setProgramCounter(uint16_t pc){
  printf("\tset pc: %d\n", pc);
  cpu_reg.PC = pc; 
}

