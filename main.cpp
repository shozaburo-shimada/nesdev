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
#include <sys/stat.h>
#include "Cpu.h"

int main(){
  printf("NES start!\n");

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

  //Read Header
  unsigned char header[16];
  fread(header, 1, sizeof(header), fp);

  file_size = stbuf.st_size;
  printf("File size is %ld bytes\n", file_size);

  fclose(fp);

  Cpu cpu = Cpu();
  //uint8_t sts = cpu.getStatusReg();
  //printf("sts: %d \n", sts);

  return 0;
}