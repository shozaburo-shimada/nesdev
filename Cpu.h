#ifndef H_CPU
#define H_CPU

#include <stdint.h>
#include "Cassette.h"


class Cpu{
  public:
    Cpu(Cassette*);
    uint8_t run();
    uint8_t fetch();
    uint8_t read(uint16_t);
    void fetchOpeland(uint8_t, uint16_t*);
    void exec(uint8_t, uint16_t, uint8_t);
    uint8_t getStatusReg();
    uint16_t getProgramCounter();
    void setProgramCounter(uint16_t);
  private:
    Cassette *rom;
    void init();
};

#endif