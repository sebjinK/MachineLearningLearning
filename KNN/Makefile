CC=g++
CPPFLAGS=-Wall -Wextra -std=c++11 -DEUCLID
SRC=main.cpp src/knn.cpp ../src/data.cpp ../src/dataHandler.cpp

all: main

main: $(SRC)
	$(CC) $(CPPFLAGS) $(SRC) -o $@ 

run: main
	./$<

clean:
	rm main