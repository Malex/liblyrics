
CC	= g++
CFLAGS	= -Wall -Wextra -pedantic -pedantic-errors -I./include/
INCL	= include
DIR	= src
BIN	= bin
EXMPL	= examples

all : types crawler dbinterface
	 if [[ ! -e $(BIN)/ ]]; then mkdir $(BIN); fi

examples : typesTest crawlerTest dbinterfaceTest

clean :
	rm -rf $(BIN)/* $(EXMPL)/*.example $(EXMPL)/*.db

types : $(INCL)/types.hpp $(DIR)/types.cpp
	$(CC) -c $(CFLAGS) $(DIR)/types.cpp -o $(BIN)/types.o

crawler : types $(INCL)/crawler.hpp $(DIR)/crawler.cpp
	$(CC) -c $(CFLAGS) $(DIR)/crawler.cpp -o $(BIN)/crawler.o

dbinterface : types $(INCL)/dbinterface.hpp $(DIR)/dbinterface.cpp
	$(CC) -c $(CFLAGS) $(DIR)/dbinterface.cpp -o $(BIN)/dbinterface.o

typesTest : types ./examples/typesTest.cpp
	$(CC) $(CFLAGS) $(EXMPL)/typesTest.cpp -o $(EXMPL)/typesTest.example  $(BIN)/types.o

crawlerTest : crawler ./examples/crawlerTest.cpp
	 $(CC) $(CFLAGS) $(EXMPL)/crawlerTest.cpp -o $(EXMPL)/crawlerTest.example $(BIN)/crawler.o $(BIN)/types.o -l curl

dbinterfaceTest : dbinterface ./examples/dbinterfaceTest.cpp
	$(CC) $(CFLAGS) $(EXMPL)/dbinterfaceTest.cpp -o $(EXMPL)/dbinterfaceTest.example $(BIN)/dbinterface.o $(BIN)/types.o -l sqlite3
