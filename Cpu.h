#ifndef H_CPU
#define H_CPU

#include <stdint.h>
#include "Cassette.h"

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



class Cpu{
  public:
    Cpu();
    void run();
    uint8_t fetch(Cassette*);
    uint8_t getStatusReg();
    uint16_t getProgramCounter();
    void setProgramCounter(uint16_t);
  private:
    void init();
};

#endif