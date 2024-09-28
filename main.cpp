#include <iostream>
//#include "data.cpp"
#include "dataHandler.hpp"

int main()
{
    DataHandler * dh = new DataHandler();
    dh->readFeatureVector("t10k-images.idx3-ubyte");// read from MNIST
    dh->readFeatureLabels("t10k-labels.idx1-ubyte"); //read from MNIST
    //srand(time(0));
    dh->splitData();
    dh->countClasses();
}