#
# Makefile
# CS50
#

all: find generate

find: find.c helpers.c helpers.h
	cc -O0 -std=c11 -Wall -Werror -o find find.c helpers.c -lcs50 -lm

generate: generate.c
	cc -O0 -std=c11 -Wall -Werror -o generate generate.c

clean:
	rm -f *.o a.out core find generate
