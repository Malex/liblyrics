
CC	= g++
CFLAGS	= -Wall -Wextra -pedantic -pedantic-errors -I./include/
INCL	= include
DIR	= src
BIN	= bin
EXMPL	= examples

all : types crawler dbinterface 
# dispatcher

examples : typesTest crawlerTest dbinterfaceTest
# dispatcherTest

clean :
	rm -rf $(BIN)/* $(EXMPL)/*.example $(EXMPL)/*.db

types : $(INCL)/types.hpp $(DIR)/types.cpp
	if [ ! -d $(BIN) ]; then mkdir $(BIN); fi   
	$(CC) -c $(CFLAGS) $(DIR)/types.cpp -o $(BIN)/types.o

crawler : types $(INCL)/crawler.hpp $(DIR)/crawler.cpp
	$(CC) -c $(CFLAGS) $(DIR)/crawler.cpp -o $(BIN)/crawler.o

dbinterface : types $(INCL)/dbinterface.hpp $(DIR)/dbinterface.cpp
	$(CC) -c $(CFLAGS) $(DIR)/dbinterface.cpp -o $(BIN)/dbinterface.o

dispatcher : types crawler dbinterface $(INCL)/dispatcher.hpp $(DIR)/dispatcher.cpp
	$(CC) -c $(CFLAGS) $(DIR)/dispatcher.cpp -o $(BIN)/dispatcher.o 

typesTest : types $(EXMPL)/typesTest.cpp
	$(CC) $(CFLAGS) $(EXMPL)/typesTest.cpp -o $(EXMPL)/typesTest.example  $(BIN)/types.o

crawlerTest : crawler $(EXMPL)/crawlerTest.cpp
	 $(CC) $(CFLAGS) $(EXMPL)/crawlerTest.cpp -o $(EXMPL)/crawlerTest.example $(BIN)/crawler.o $(BIN)/types.o -l curl

dbinterfaceTest : dbinterface $(EXMPL)/dbinterfaceTest.cpp
	$(CC) $(CFLAGS) $(EXMPL)/dbinterfaceTest.cpp -o $(EXMPL)/dbinterfaceTest.example $(BIN)/dbinterface.o $(BIN)/types.o -l sqlite3

dispatcherTest : dispatcher $(EXMPL)/dispatcherTest.cpp
	$(CC) $(CFLAGS) $(EXMPL)/dispatcherTest.cpp -o $(EXMPL)/dispatcherTest.example $(BIN)/dispatcher.o $(BIN)/types.o $(BIN)/dbinterface.o $(BIN)/crawler.o -l curl -l sqlite3

