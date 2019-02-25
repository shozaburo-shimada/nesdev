/*
The MIT License (MIT)

Copyright (c) 2018 Shozaburo Shimada

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h> //malloc()
#include <sys/stat.h> //stat()
#include <string.h> //strcmp()
#include "Cpu.h"

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

int main(){

  FILE *fp;
  //int fd;
  char *file_buf;
  long file_size;
  struct stat stbuf;

  char filename[] = "sample1.nes";

  fp = fopen(filename, "rb");
  if(fp == NULL){
    printf("ERROR: %s can't be opened\n", filename);
    return -1;
  } else{
    printf("%s is opened\n", filename);
  }

  if(stat(filename, &stbuf) != 0){
    printf("ERROR: stat()\n");
    return -1;
  }

  file_size = stbuf.st_size;
  printf("File size is %ld bytes\n", file_size);

  struct Header *header;
  header = (struct Header*)malloc(sizeof(struct Header));

  //Parse header of nes file

  fread(header, sizeof(unsigned char), 16, fp);

  printf("Magic Number: %x, %x, %x %x \n", header->magic_number[0], header->magic_number[1], header->magic_number[2], header->magic_number[3]);  

  if(memcmp(MAGIC, header->magic_number, sizeof(unsigned char) * 4) != 0){
    printf("This file is wrong format\n");
  }

  printf("Program ROM size: %d x 16KB \n", header->prg_size);
  printf("Character ROM size: %d x 8KB \n", header->chr_size);
  
  free(header);
  fclose(fp);

  Cpu cpu = Cpu();

  return 0;
}