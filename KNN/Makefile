CC=g++
CPPFLAGS=-Wall -Wextra -std=c++11 -DEUCLID
all: main

main: libdir objdir obj/dataHandler.cpp obj/data.o
	$(CC) $(CPPFLAGS) $(SRC) -o $@ 

run: main
	./$<

clean:
	rm main