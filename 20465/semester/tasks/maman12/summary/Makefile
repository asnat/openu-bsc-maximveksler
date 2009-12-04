CC = gcc
CFLAGS = -g -Wall -ansi
LFLAGS = 

LIBS = 
OBJS = manipulation.o summary.o
SRCS = $(OBJS:.o=.c)

all: summary

summary:	$(OBJS)
	$(CC) -o $@ $^ $(LFLAGS) $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) -c $<


#PHONY
.PHONY: clean
clean:
	rm -f *.o *~

.PHONY: test
test: summary
	echo '1' | ./summary
	echo '1 2' | ./summary
	echo '1 2 3 4 5 6 7 8 9 10' | ./summary
	echo '34 2348 234 234 839 234 90238 493 948328 949 9203 0938203 03820 0492 8 040293 80238 92093 83' | ./summary
	echo '' | ./summary

