CFLAGS = -Wall -Wshadow -O3 -g -march=native
LDLIBS = -lm

all: main 

sigmoid: CFLAGS += -Dgenann_act=genann_act_sigmoid_cached
sigmoid: all

threshold: CFLAGS += -Dgenann_act=genann_act_threshold
threshold: all

linear: CFLAGS += -Dgenann_act=genann_act_linear
linear: all

test: test.o genann.o commonFunctions.o
main: main.o genann.o commonFunctions.o 

check: test
	./$^

clean:
	$(RM) *.o
	$(RM) test example1 example2 example3 example4 *.exe
	$(RM) persist.txt

.PHONY: sigmoid threshold linear clean
