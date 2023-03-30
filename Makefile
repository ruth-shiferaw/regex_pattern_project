#Ruth Shiferaw
#JHED ID: RSHIFER1
#should compile the hw3 executable with the command make hw3, 
#and create AND run the test executable with the command make test.
# Homework 3

GCC = gcc
CONSERVATIVE_FLAGS = -std=c99 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

test: test_functions
	./test

hw3: hw3.o functions.o #executable template
	$(GCC) -o hw3 hw3.o functions.o 

hw3.o: hw3.c functions.h #object file template
	$(GCC) -c hw3.c $(CFLAGS)

test_functions: test_functions.o functions.o
	$(GCC) -o  test test_functions.o functions.o 

test_functions.o: test_functions.c functions.c
	$(GCC) -c test_functions.c $(CFLAGS)

functions.o: functions.c functions.h
	$(GCC) -c functions.c $(CFLAGS)

clean:
	rm -f *.o hw3 test *~ 
