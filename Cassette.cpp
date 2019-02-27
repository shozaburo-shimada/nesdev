#include "Cassette.h"

#include <stdlib.h> //malloc()
#include <sys/stat.h> //stat()
#include <string.h> //strcmp()
#include <stdio.h>

Cassette::Cassette(){


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

  struct Header *header;
  header = (struct Header*)malloc(sizeof(struct Header));

  //Parse header of nes file

  fread(header, sizeof(unsigned char), 16, fp);

  printf("\tMagic Number: %x, %x, %x %x \n", header->magic_number[0], header->magic_number[1], header->magic_number[2], header->magic_number[3]);  

  if(memcmp(MAGIC, header->magic_number, sizeof(unsigned char) * 4) != 0){
    printf("\tThis file is wrong format\n");
  }

  printf("\tProgram ROM size: %d x 16KB \n", header->prg_size);
  printf("\tCharacter ROM size: %d x 8KB \n", header->chr_size);
  
  free(header);
  fclose(fp);
  
  return 0;

}