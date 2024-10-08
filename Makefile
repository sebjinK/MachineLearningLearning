CC=g++
CPPFLAGS=-Wall -Wextra -std=c++11 -DEUCLID
# SRC=main.cpp src/data.cpp src/dataHandler.cpp 
OBJS=obj/main.o obj/dataHandler.o obj/data.o obj/common.o KMEANS/obj/kmeans.o KNN/obj/knn.o 
TARGET=KNN.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o ./lib/$@

obj/main.o: ./main.cpp
	$(CC) -fPIC $(CPPFLAGS) -c $< -o $@ 
obj/data.o: ./src/data.cpp
	$(CC) -fPIC $(CPPFLAGS) -c $< -o $@ 
obj/dataHandler.o: ./src/dataHandler.cpp
	$(CC) -fPIC $(CPPFLAGS) -c $< -o $@
KNN/obj/knn.o: ./KNN/src/knn.cpp
	$(CC) -fPIC $(CPPFLAGS) -c $< -o $@
obj/common.o: ./src/common.cpp
	$(CC) -fPIC $(CPPFLAGS) -c $< -o $@
KMEANS/obj/kmeans.o: ./KMEANS/src/kmeans.cpp
	$(CC) -fPIC $(CPPFLAGS) -c $< -o $@

run: $(TARGET)
	./lib/$<
clean:
	rm ./lib/$(TARGET)
	rm ./obj/*.o
	rm ./KNN/obj/*.o
	rm ./performance/*.txt
	