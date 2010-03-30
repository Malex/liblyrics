
CC	= g++
CFLAGS	= -Wall -Wextra -pedantic -pedantic-errors -I./include/
INCL	= include
DIR	= src
BIN	= bin
EXMPL	= examples


examples : typesTest crawlerTest


typesTest : types ./examples/typesTest.cpp
	$(CC) $(CFLAGS) $(EXMPL)/typesTest.cpp -o $(EXMPL)/typesTest.example  $(BIN)/types.o
	
types : $(INCL)/types.hpp
	mkdir $(BIN)
	$(CC) -c $(CFLAGS) $(DIR)/types.cpp -o $(BIN)/types.o

crawlerTest : crawler ./examples/crawlerTest.cpp
	 $(CC) $(CFLAGS) $(EXMPL)/crawlerTest.cpp -o $(EXMPL)/crawlerTest.example $(BIN)/crawler.o $(BIN)/types.o -l curl

crawler : types $(INCL)/crawler.hpp $(DIR)/crawler.cpp
	$(CC) -c $(CFLAGS) $(DIR)/crawler.cpp -o $(BIN)/crawler.o

clean :
	rm -rf $(BIN) $(EXMPL)/*.example
