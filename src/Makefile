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
#Executable
EXE = Search

# Link the files
link : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LFLAGS) -o $(EXE)
# Create main object file
main.o : main.cpp buildWord.h readException.h TFIDF.h
	$(CC) main.cpp $(INCLUDE) $(CFLAGS)
# Create Complex object file
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

clean :
	rm -f *.o *~ $(EXE)
