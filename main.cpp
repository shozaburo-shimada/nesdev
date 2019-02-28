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
#include <pthread.h>
#include <unistd.h> //pause()

#include "Cpu.h"
#include "Cassette.h"

Cassette rom = Cassette();
Cpu cpu = Cpu();

int running;

void cpu_process(){
  printf("cpu_process()\n");
  //Fetch
  uint16_t pc = cpu.getProgramCounter();
  printf("\tprogram counter: %d\n", pc);
  cpu.setProgramCounter(++pc);
  cpu.fetch();
  //Process
}

void gpu_process(){
  printf("gpu_process()\n");
}



void *cpu_clock(void *param){
  while(running){
    usleep(1000000);
    cpu_process();
  }
  return NULL;
}

void *gpu_clock(void *param){
  while(running){
    usleep(500000);
    gpu_process();
  }
  return NULL;
}

int main(){
  printf("\n");


  pthread_t cpu_tid, gpu_tid;

  //Init Objects
  rom.init();
  cpu.run();

  //Init thread
  running = 1;
  if(pthread_create(&cpu_tid, NULL, cpu_clock, NULL) != 0){
    perror("ERROR: cpu, pthread_create()\n");
    return -1;
  }
  if(pthread_create(&gpu_tid, NULL, gpu_clock, NULL) != 0){
    perror("ERROR: gpu, pthread_create()\n");
    return -1;
  }

  while(getchar() != 'q');
  running = 0;
  pthread_join(cpu_tid, NULL);

  //while(1);

  printf("\n");
  return 0;
}