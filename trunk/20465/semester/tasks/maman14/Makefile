APPBIN = assembler
CC = gcc
CFLAGS = -g -Wall -ansi
LFLAGS = 

LIBS = -lm
OBJS = $(APPBIN).o #.... lots and lots of stuff here...
SRCS = $(OBJS:.o=.c)

all: $(APPBIN)

$(APPBIN):	$(OBJS)
	$(CC) -o $@ $^ $(LFLAGS) $(LIBS)

%.o:%.c 
	$(CC) $(CFLAGS) -c $<


#PHONY
.PHONY: clean
clean:
	rm -f *.o *~ $(APPBIN)
