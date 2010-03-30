
CC	= g++
CFLAGS	= -Wall -Wextra -pedantic -pedantic-errors -I./include/
INCL	= include
DIR	= src
BIN	= bin
EXMPL	= examples


examples : typesTest


typesTest : types ./examples/typesTest.cpp
	$(CC) $(CFLAGS) $(EXMPL)/typesTest.cpp -o $(EXMPL)/typesTest.example  $(BIN)/types.o
	
types : $(INCL)/types.hpp
	mkdir $(BIN)
	$(CC) -c $(CFLAGS) $(DIR)/types.cpp -o $(BIN)/types.o

clean :
	rm -rf $(BIN) $(EXMPL)/*.example
