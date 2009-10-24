_CC = gcc
CFLAGS = -Wall -ansi -pedantic
LFLAGS = 

LIBS = 
OBJS = abc.o
SRCS = $(OBJS:.o=.c)

all: abc

abc:	$(OBJS)
	$(CC) -o $@ $^ $(LFLAGS) $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) -c $<


#PHONY
.PHONY: clean
clean:
	rm -f *.o *~
