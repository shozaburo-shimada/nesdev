#include <stdint.h>

const unsigned char MAGIC[] = {0x4e, 0x45, 0x53, 0x1a};

struct Header {
  unsigned char magic_number[4]; //4E, 45, 53, 1A
  unsigned char prg_size; //Size of program ROM
  unsigned char chr_size; //Size of character ROM
  unsigned char flag_6;
  unsigned char flag_7;
  unsigned char flag_8;
  unsigned char flag_9;
  unsigned char flag_10;
  unsigned char reserved[5];
};

class Cassette{
  public:
    Cassette();
    uint8_t init(); 
};