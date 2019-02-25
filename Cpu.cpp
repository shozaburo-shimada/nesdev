#include "Cpu.h"
#include <stdio.h>

static registers_t cpu_reg;

Cpu::Cpu(){
  
  cpu_reg.P.sts_bits.negative = true;
  cpu_reg.P.sts_bits.overflow = true;
  cpu_reg.P.sts_bits.reserve = false;
  cpu_reg.P.sts_bits.break_mode = true;
  cpu_reg.P.sts_bits.decimal_mode = true;
  cpu_reg.P.sts_bits.interrupt = true;
  cpu_reg.P.sts_bits.zero = true;
  cpu_reg.P.sts_bits.carry = true;
  
  printf("CPU REGS: %d \n", cpu_reg.P.sts_8);
}

void Cpu::run(){
  printf("CPU REGS: %d \n", cpu_reg.P.sts_8);
}

uint8_t getStatusReg(){
  return cpu_reg.P.sts_8;
}