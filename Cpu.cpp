#include <stdio.h>

#include "Cpu.h"

static cpu_registers_t cpu_reg;

Cpu::Cpu(){

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

void Cpu::run(){
  printf("Cpu::run()\n");
  init();

}

void Cpu::fetch(){

}

uint8_t Cpu::getStatusReg(){
  return cpu_reg.P.sts_byte;
}

uint16_t Cpu::getProgramCounter(){
  return cpu_reg.PC;  
}

void Cpu::setProgramCounter(uint16_t pc){
  printf("\t set pc: %d\n", pc);
  cpu_reg.PC = pc; 
}

