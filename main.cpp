// #include "../src/data.cpp"
// #include "../src/dataHandler.cpp"
// #include "./src/knn.cpp"
#include "./KNN/src/knn.hpp"
#include <iostream>

int main()
{
    DataHandler * dh = new DataHandler();
    dh->readFeatureVector("./images&labels/t10k-images.idx3-ubyte");// read from MNIST
    dh->readFeatureLabels("./images&labels/t10k-labels.idx1-ubyte"); //read from MNIST
    //srand(time(0));
    dh->splitData();
    dh->countClasses();
    KNN * knearest = new KNN();
    knearest->setTrainingData(dh->getTrainingData());
    knearest->setTestData(dh->getTestData());
    knearest->setValidationData(dh->getValidationData());
    double performance = 0;
    double bestPerformance = 0;

    int bestK = 1;
    for (int i = 1; i <= 4; i++)
    {
        if (i == 1)
        {
            knearest->setK(i);
            performance = knearest->validatePerformance();
            bestPerformance = performance;
        }
        else
        {
            knearest->setK(i);
            performance = knearest->validatePerformance();
            if (performance > bestPerformance)
            {
                bestPerformance = performance;
                bestK = i;
            }
        }
    }
    knearest->setK(bestK);
    knearest->testPerformance();
}