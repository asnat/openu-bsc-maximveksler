CC = gcc
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

.PHONY: test
test: abc
	echo 'HelloWorld' | ./abc
	echo 'abd' | ./abc
	echo 'abc' | ./abc
	echo ':;<=>?' | ./abc
	echo '>?@ABC' | ./abc
	echo 'XYZ[' | ./abc
	echo '^_\`abc' | ./abc
	echo 'xyz{' | ./abc
	echo 'abcHHHABCDEFiiilmn' | ./abc
	echo 'dabcemoqmnopqrrtaduvwxaz' | ./abc

