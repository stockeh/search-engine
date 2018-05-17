# Compiler
CC = g++ -std=c++14 -lpthread
# Compilation Flag
CFLAGS = -Wall -c -g -O3
# Linking Flag
LFLAGS = -Wall -g
# Object Files
OBJS = main.o stemming.o readException.o buildWord.o ExceptionCapital.o TFIDF.o
# Include header files
INCLUDE = -I.
#Executables
EXE1 = Search
EXE2 = Server

# Build all
all: link server

# Link the server files
server : rest_server.o
	$(CC) rest_server.o -lpistache $(LFLAGS) -o $(EXE2)

# Create server object file
rest_server.o : rest_server.cpp
	$(CC) rest_server.cpp $(CFLAGS)

# Link the search files
link : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LFLAGS) -o $(EXE1)

# Create object files
main.o : main.cpp buildWord.h readException.h TFIDF.h
	$(CC) main.cpp $(INCLUDE) $(CFLAGS)

buildWord.o : buildWord.cpp buildWord.h ExceptionCapital.h
	$(CC) buildWord.cpp $(INCLUDE) $(CFLAGS)

stemming.o : stemming.cpp stemming.h
	$(CC) stemming.cpp $(INCLUDE) $(CFLAGS)

readException.o : readException.cpp readException.h
	$(CC) readException.cpp $(INCLUDE) $(CFLAGS)

ExceptionCapital.o : ExceptionCapital.cpp ExceptionCapital.h stemming.h buildWord.h
	$(CC) ExceptionCapital.cpp $(INCLUDE) $(CFLAGS)

TFIDF.o : TFIDF.cpp TFIDF.h buildWord.h
	$(CC) TFIDF.cpp $(INCLUDE) $(CFLAGS)

# Clean Directory
clean :
	rm -f *.o *~ $(EXE1) $(EXE2)
