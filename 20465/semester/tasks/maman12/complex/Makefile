APPBIN = complex
CC = gcc
CFLAGS = -g -Wall -ansi
LFLAGS = 

LIBS = -lm
OBJS = main.o complex.o
SRCS = $(OBJS:.o=.c)

all: $(APPBIN)

$(APPBIN):	$(OBJS)
	$(CC) -o $@ $^ $(LFLAGS) $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) -c $<


#PHONY
.PHONY: clean
clean:
	rm -f *.o *~
