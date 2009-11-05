CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
LFLAGS = 

LIBS = 
OBJS = doll.o
SRCS = $(OBJS:.o=.c)

all: doll

doll:	$(OBJS)
	$(CC) -o $@ $^ $(LFLAGS) $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) -c $<


#PHONY
.PHONY: clean
clean:
	rm -f *.o *~
