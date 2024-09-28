CPP=g++
CPPFLAGS=-Wall -Wextra -std=c++11
SRC=main.cpp data.cpp dataHandler.cpp 
OBJS=dataHandler.o data.o
TARGET=libdata.so



all:$(TARGET)

$(TARGET):$(SRC)
	$(CPP) $(CPPFLAGS) $(SRC) -o $(TARGET)

run:$(TARGET)
	./$(TARGET)
clean:
	rm $(TARGET)
	