#include "Cpu.h"

#include <stdio.h>

static cpu_registers_t cpu_reg;

Cpu::Cpu(){

}

void Cpu::init(){
  printf("Cpu::init()\n");
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

uint8_t Cpu::getStatusReg(){
  return cpu_reg.P.sts_byte;
}
