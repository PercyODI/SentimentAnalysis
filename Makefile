BIN = hw4
CC = gcc
CFLAGS = -g -Wall

$(BIN): runner.o words.o analysis.o
	$(CC) $(CFLAGS) runner.o words.o analysis.o -o $(BIN)

runner.o: runner.c words.h analysis.h
	$(CC) $(CFLAGS) -c runner.c

analysis.o: analysis.c analysis.h
	$(CC) $(CFLAGS) -c analysis.c

words.o: words.c words.h
	$(CC) $(CFLAGS) -c words.c

clean:
	rm *.o $(BIN)