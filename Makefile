CC=g++
CPPFLAGS=-Wall -Wextra -std=c++11
# SRC=main.cpp src/data.cpp src/dataHandler.cpp 
OBJS=dataHandler.o data.o
TARGET=libdata

all:$(TARGET)

$(TARGET): obj/dataHandler.o obj/data.o KNN/obj/knn.o
	$(CC) $(CPPFLAGS) -c main.cpp obj/data.o obj/dataHandler.o KNN/obj/knn.o -o $./lib/$(TARGET)

obj/data.o: ./src/data.cpp
	$(CC) -fPIC $(CPPFLAGS) -c $< -o $@ 
obj/dataHandler.o: ./src/dataHandler.cpp
	$(CC) -fPIC $(CPPFLAGS) -c $< -o $@
KNN/obj/knn.o: ./KNN/src/knn.cpp
	$(CC) -fPIC $(CPPFLAGS) -c $< -o $@

run: $./lib/$(TARGET)
	./$<
clean:
	rm $./lib/$(TARGET)
	