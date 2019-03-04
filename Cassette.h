#ifndef H_CASSETTE
#define H_CASSETTE

#include <stdint.h>

const unsigned char MAGIC[] = {0x4e, 0x45, 0x53, 0x1a};

/* Flag6 
  bit 0     1 for vertical mirroring, 0 for horizontal mirroring
  bit 1     1 for battery-backed RAM at $6000-$7FFF
  bit 2     1 for a 512-byte trainer at $7000-$71FF
  bit 3     Reserved
  bit 4-7   Type of ROM bank selector
      0 - None
      1 - Megaman2,Bomberman2,Destiny,etc.
      2 - Castlevania,LifeForce,etc.
      3 - QBert,PipeDream,Cybernoid,etc.
      4 - SilverSurfer,SuperContra (experimental)
      8 - F3xxx carts off FFE CDROM (experimental)
      15 - 100-in-1 cartridge (experimental)
*/
typedef struct flag6_bits{
  uint8_t mirroring:1;  //bit0
  uint8_t battery:1;    //bit1
  uint8_t trainer:1;    //bit2
  uint8_t reserved:1;   //bit3
  uint8_t bank:4;       //bit4 - bit7
}flag6_bits_t;


struct Header {
  uint8_t magic_number[4]; //4E, 45, 53, 1A
  uint8_t prg_size; //Size of program ROM
  uint8_t chr_size; //Size of character ROM

  union {
    uint8_t bytes;
    flag6_bits_t bits;
  }flag6;
  uint8_t flag7;
  uint8_t flag8;
  uint8_t flag9;
  uint8_t flag10;
  uint8_t reserved[5];
};

class Cassette{
  public:
    Cassette();
    ~Cassette();
    uint8_t init(); 
    uint8_t getData(uint16_t);
};

#endif