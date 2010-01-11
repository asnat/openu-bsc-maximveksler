APPBIN = min_call
CC = gcc
CFLAGS = -g -Wall -ansi
LFLAGS = 

LIBS = -lm
OBJS = $(APPBIN).o
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
