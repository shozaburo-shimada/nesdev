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

  BaseName basename = ope_list[opecode].base;
  Addressing addressing = ope_list[opecode].add;
  uint8_t cyc = ope_list[opecode].cycles;

  printf("\topecode: 0x%x, base: %d, addressing: %d, cycle: %d \n", opecode, basename, addressing, cyc);

  //Fetch Opeland
  uint16_t opeland;
  this->fetchOpeland(addressing, &opeland);
  if(&opeland == NULL){
    printf("\topeland: NULL \n");
  }else{
    printf("\topeland: 0x%x \n", opeland);
  }

  //Execute
  this->exec(basename, opeland, addressing);

  return cycle;
}

uint8_t Cpu::fetch(){
  printf("Cpu::fetch()\n");
  this->rom->getData(cpu_reg.PC++);
}

void Cpu::fetchOpeland(uint8_t addressing, uint16_t *opl){
  printf("Cpu::fetchOpeland()\n");
  
  uint8_t baseaddr;

  switch(addressing){
    case IMPLIED:
      printf("\tIMPLIED \n");
      *opl = 0;
      break;
    case ACCUMULATOR:
      *opl = 0;
      break;
    case IMMEDIATE:
      *opl = this->fetch();
      break;
    case ZERO_PAGE:
      *opl = this->fetch();
      break;
    case ZERO_PAGE_X:
      *opl = 0x00FF & (this->fetch() + cpu_reg.X);
      break;
    case ZERO_PAGE_Y:
      *opl = 0x00FF & (this->fetch() + cpu_reg.Y);
      break;
    case RELATIVE:
      baseaddr = this->fetch();
      if(baseaddr < 0x80){
        *opl = baseaddr + this->fetch();
      }else{
        *opl = baseaddr + this->fetch() - 256;
      }
      break;
    case ABSOLUTE:
      baseaddr = this->fetch();
      *opl = this->fetch() << 8 | baseaddr;
      break;
    case ABSOLUTE_X:
      baseaddr = this->fetch();
      *opl = this->fetch() << 8 | baseaddr;
      *opl = 0xFFFF & (*opl + cpu_reg.X);
      break;
    case ABSOLUTE_Y:
      baseaddr = this->fetch();
      *opl = this->fetch() << 8 | baseaddr;
      *opl = 0xFFFF & (*opl + cpu_reg.Y);
      break;
    case INDIRECT:

      break;
    case INDIRECT_X:
      baseaddr = 0xFF & (this->fetch() + cpu_reg.X);
      *opl = this->fetch() << 8 | baseaddr;
      break;
    case INDIRECT_Y:
      baseaddr = this->fetch();
      *opl = 0xFFFF & ((this->fetch() << 8 | baseaddr) + cpu_reg.Y);
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
