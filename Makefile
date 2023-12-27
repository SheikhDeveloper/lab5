CFLAGS = -Wall -Wextra -Werror -g 
ASAN = -fsanitize=address,undefined
EXEC = lab5_1 lab5_2 debug_1 debug_2
SRCS = $(shell find . -type f -name '*.c' -print)
HEADERS = $(shell find . -name 'lib' -type d -prune -o -type f -name '*.h' -print)
STATIC = --analyze -Xanalyzer -analyzer-output=html
 
CC = clang

all: lab5_1 lab5_2

lab5_1: voters.o file_manager.o sort.o main.o 
	${CC} ${ASAN} voters.o file_manager.o sort.o main.o -o $@

lab5_2: voters.o sort.o generator.o timer.o
	${CC} ${ASAN} voters.o generator.o timer.o -o $@ 

voters.o : lib/voters.c lib/voters.h
	${CC} ${CFLAGS} ${ASAN} -c lib/voters.c -o $@

file_manager.o: lib/file_manager.c lib/file_manager.h
	${CC} ${CFLAGS} ${ASAN} -c lib/file_manager.c -o $@

sort.o: lib/sort.c lib/sort.h
	${CC} ${CFLAGS} ${ASAN} -c lib/sort.c -o $@

generator.o: lib/generator.c lib/generator.h
	${CC} ${CFLAGS} ${ASAN} -c lib/generator.c -o $@

timer.o: timer.c
	${CC} ${CFLAGS} ${ASAN} -c timer.c -o $@

main.o : main.c
	${CC} ${CFLAGS} ${ASAN} -c main.c -o $@

debug: ${SRCS} ${HEADERS}
	${CC} -c ${CFLAGS} ./lib/*.c 
	${CC} -c ${CFLAGS} main.c -o main.o
	${CC} -c ${CFLAGS} timer.c -o timer.o
	${CC} voters.o file_manager.o sort.o main.o -o $@_1
	${CC} voters.o generator.o timer.o -o $@_2

.PHONY : lab5_1 lab5_2 clean static debug

static:
	${CC} lib/voters.c ${STATIC} -o voters
	${CC} lib/file_manager.c ${STATIC} -o file_manager
	${CC} lib/sort.c ${STATIC} -o sort
	${CC} main.c ${STATIC} -o main

clean: 
	rm -rf ${EXEC}
	rm -rf *.o
