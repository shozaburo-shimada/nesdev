PROGRAM = nes
OBJS = main.o Cpu.o
CC = gcc
CFLAGS =
LDFLAGS =

#nes: main.o Cpu.o
#	$(CC) -o nes main.o Cpu.o

#main.o:
#	$(CC) -c main.c

#Cpu.o:
#	$(CC) -c Cpu.c

$(PROGRAM):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)
