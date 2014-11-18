#  file:     Makefile
#  Author  - John Allard
#  CruzID  - jhallard
#  Class   - CS12M, Lab #5
#  Date    - Nov 16th, 2014
#  Prupose - This file will build the list file and run a valgrind memory test on it */

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wfatal-errors -g
OBJS = list.o
OUTPUT = list
HEADERS = list.c

${OUTPUT}: ${OBJS}
	${CC} $< -o ${OUTPUT}

%.o: %.c ${HEADERS}
	${CC} -c ${CFLAGS} $<

clean:
	rm -f *.o

spotless: clean
	rm -f ${OUTPUT}

test: ${OUTPUT}
	valgrind ./${OUTPUT}

.PHONY: clean spotless test

