#include "Cassette.h"

#include <stdlib.h> //malloc()
#include <sys/stat.h> //stat()
#include <string.h> //strcmp()
#include <stdio.h>

struct Header *header;
uint8_t *prg_rom;
uint8_t *chr_rom;
uint8_t trainer[512];

Cassette::Cassette(){
  printf("Create Cassette Instance\n");
}

Cassette::~Cassette(){
  printf("Delete Cassette Instance\n");

  free(prg_rom);
  free(chr_rom);
  free(header);
}



uint8_t Cassette::init(){
  printf("Cassette::init()\n");

  FILE *fp;
  //int fd;
  char *file_buf;
  long file_size;
  struct stat stbuf;

  char filename[] = "sample1.nes";

  fp = fopen(filename, "rb");
  if(fp == NULL){
    printf("\tERROR: %s can't be opened\n", filename);
    return -1;
  } else{
    printf("\t%s is opened\n", filename);
  }

  if(stat(filename, &stbuf) != 0){
    printf("\tERROR: stat()\n");
    return -1;
  }

  file_size = stbuf.st_size;
  printf("\tFile size is %ld bytes\n", file_size);


  header = (struct Header*)malloc(sizeof(struct Header));

  //Parse header of nes file

  fread(header, sizeof(unsigned char), 16, fp);

  printf("\tMagic Number: %x, %x, %x %x \n", header->magic_number[0], header->magic_number[1], header->magic_number[2], header->magic_number[3]);  

  if(memcmp(MAGIC, header->magic_number, sizeof(unsigned char) * 4) != 0){
    printf("\tThis file is wrong format\n");
  }

  printf("\tProgram ROM size: %d x 16KB \n", header->prg_size);
  printf("\tCharacter ROM size: %d x 8KB \n", header->chr_size);
  printf("\tFlag 6: %d \n", header->flag6.bytes);
  printf("\tFlag 7: %d \n", header->flag7);
  printf("\tFlag 8: %d \n", header->flag8);
  printf("\tFlag 9: %d \n", header->flag9);
  printf("\tFlag 10: %d \n", header->flag10);

  prg_rom = (uint8_t *)malloc(header->prg_size * 16 * 1024);
  chr_rom = (uint8_t *)malloc(header->chr_size * 8 * 1024);

  if(header->flag6.bits.trainer){
    fread(trainer, sizeof(uint8_t), sizeof(trainer), fp);
  }

  fread(prg_rom, sizeof(uint8_t), header->prg_size * 16 * 1024, fp);
  fread(chr_rom, sizeof(uint8_t), header->chr_size * 8 * 1024, fp);

  fclose(fp);
  return 0;

}


uint8_t Cassette::getData(uint16_t pc){
  printf("Cassette::getData()\n");
  return prg_rom[pc];
}