#  file:     Makefile
#  Author  - John Allard, template provided by Prof Whitehead.
#  CruzID  - jhallard
#  Class   - CS12M, Lab #4
#  Date    - Nov 7th, 2014
#  Prupose - This file will build the circular queue and the testing suite for it. */

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wfatal-errors -g
OBJS = queue.o
OUTPUT = queue
HEADERS = minunit.h

${OUTPUT}: ${OBJS}
	${CC} $< -o ${OUTPUT}

%.o: %.c ${HEADERS}
	${CC} -c ${CFLAGS} $<

clean:
	rm -f *.o

spotless: clean
	rm -f ${OUTPUT}

test: ${OUTPUT}
	./${OUTPUT}

.PHONY: clean spotless test

