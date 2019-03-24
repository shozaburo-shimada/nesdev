#include <stdio.h>
#include "Cpu.h"
#include "Instruction.h"

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

  //Fetch Opecode from program rom
  printf("\tprogram counter: %d \n", cpu_reg.PC);
  uint8_t opecode = this->fetch();

  uint8_t basename = ope_list[opecode].base;
  uint8_t addressing = ope_list[opecode].add;
  uint8_t cyc = ope_list[opecode].cycles;

  printf("\topecode: 0x%x, base: %d, addressing: %d, cycle: %d \n", opecode, basename, addressing, cyc);

  //Fetch Opeland
  uint8_t opeland;
  this->fetchOpeland(addressing, &opeland);


  //Execute
  this->exec(basename, opeland, addressing);

  return cycle;
}

uint8_t Cpu::fetch(){
  printf("Cpu::fetch()\n");
  this->rom->getData(cpu_reg.PC++);
}

void Cpu::fetchOpeland(uint8_t addressing, uint8_t *opl){
  printf("Cpu::fetchOpeland()\n");
  
  switch(addressing){
    case IMPLIED:
      opl = NULL;
      break;
    case ACCUMULATOR:
      opl = NULL;
      break;
    case IMMEDIATE:
      *opl = this->fetch();
      break;
    case ZERO_PAGE:
      *opl = this->fetch();
      break;
    case ZERO_PAGE_X:
      *opl = this->fetch() + cpu_reg.X;
      break;
    case ZERO_PAGE_Y:
      *opl = this->fetch() + cpu_reg.Y;
      break;
    case RELATIVE:
      break;
    case ABSOLUTE:
      break;
    case ABSOLUTE_X:
      break;
    case ABSOLUTE_Y:
      break;
    case INDIRECT:
      break;
    case INDIRECT_X:
      break;
    case INDIRECT_Y:
      break;
    default:
      break; 

  }
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
