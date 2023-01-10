CFLAGS = -Wall -Wshadow -O3 -g -march=native
LDLIBS = -lm

SRC := $(wildcard src/*.c)
main: FORCE

FORCE:
	gcc $(SRC) -o ./obj/main.o $(CFLAGS) $(LDLIBS) 
