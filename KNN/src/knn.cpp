#include "knn.hpp"
#include <cmath>
#include <limits>
#include <map>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "stdint.h"
//#include "../data.hpp"

KNN::KNN(int val)
{
    k = val;
}
KNN::KNN()
{
    //NOTHING TO DO
}
KNN::~KNN()
{
    //NOTHING TO DO
}
void KNN::setTrainingData(std::vector<data *> * vect1)
{
    trainingData = vect1;
}
void KNN::setTestData(std::vector<data *> * vect1)
{
    testData = vect1;
}
void KNN::setValidationData(std::vector<data *> * vect1)
{   
    validationData = vect1;
}
void KNN::setK(int val)
{
    k = val;
}
void KNN::findKNearest(data *queryPoint)
{
    neighbors = new std::vector<data *>;
    double min = std::numeric_limits<double>::max();
    double prevMin = min;
    int index = 0;
    for (int i = 0; i < k; i++)
    {
        if(i == 0)
        {
            for (int j = 0; j < trainingData->size(); j++)
            {
                double distance = calculateDistance(queryPoint, trainingData->at(j));
                trainingData->at(j)->setDistance(distance);
                if (distance < min)
                {
                    min = distance;
                    index = j;
                }
            }
            neighbors->push_back(trainingData->at(index));
            prevMin = min;
            min = std::numeric_limits<double>::max();
        }
        else
        {
            for (int j = 0; j < trainingData->size(); j++)
            {
                double distance = calculateDistance(queryPoint, trainingData->at(j));
                if (distance < min && distance != prevMin)
                {
                    min = distance;
                    index = j;
                }
            }
            neighbors->push_back(trainingData->at(index));
            prevMin = min;
            min = std::numeric_limits<double>::max();
        }
    }
}
int KNN::predict()
{
    std::map<uint8_t, int> classFrequencies;
    for (int i = 0; i < neighbors->size(); i++)
    {
        if (classFrequencies.find(neighbors->at(i)->getLabel()) == classFrequencies.end())
        {
            classFrequencies[neighbors->at(i)->getLabel()] = 1;
        }
        else
        {
            classFrequencies[neighbors->at(i)->getLabel()]++;
        }
    }
    int best = 0; // best class
    int max = 0; // max counted class
    for (auto kv : classFrequencies)
    {
        //std::cout << kv.first << " -> " << kv.second << '\n';
        if(kv.second > max)
        {
            max = kv.second;
            best = kv.first;
        }
    }
    delete neighbors;
    return best;
} // return the predicted class

double KNN::calculateDistance(data * queryPoint, data * input) 
{
    double distance = 0.0;
    if (queryPoint->getFeatureVectorSize() != input->getFeatureVectorSize())
    {
        std::cerr << "Error Vector Size Mismatch\n";
        exit(1);
    }
    #ifdef EUCLID
        for (unsigned i = 0; i < queryPoint->getFeatureVectorSize(); i++)
        {
            // calculation for EUCLID is sqrt(sum(linear combinations of the dot products))
            distance += pow(queryPoint->getFeatureVector()->at(i) - input->getFeatureVector()->at(i), 2);
        }
        distance = sqrt(distance);
    #elif defined MANHATTAN
        // PUT MANHATTEN IMPLMENTATION HERE
    #endif
    return distance;
}// calculate using euclidean distance but also make a placeholder to learn manhatten disantces
double KNN::validatePerformance()
{
    //double currentPerformance = 0;
    std::ofstream FILE;
    FILE.open("./performance/validation.txt");
    int count = 0;
    int dataIndex = 0;
    for (data *queryPoint : *validationData)
    {
        findKNearest(queryPoint);
        int prediction = predict();
        std::cout << prediction << " -> " << (int)queryPoint->getLabel() << ".\n";
        if(prediction == queryPoint->getLabel())
            count++;
        dataIndex++;
        std::cout << "Current Performance = " << std::fixed << std::setprecision(3) << ((double) count * 100)/((double) dataIndex) << '\n';
    }
    std::cout << "Validation Performance = " << std::fixed << std::setprecision(3) << ((double) count * 100)/((double) validationData->size()) << '\n';
    if (FILE.is_open())    
        FILE << "Validation Performance = " << std::fixed << std::setprecision(3) << ((double) count * 100)/((double) validationData->size()) << '\n';
    FILE.close();
    return ((double) count * 100)/((double) validationData->size());
} //Pick correct K value (validation data)
double KNN::testPerformance()
{
    //double currentPerformance = 0;
    std::ofstream FILE;
    FILE.open("./performance/test.txt");
    int count = 0;
    int dataIndex = 0;
    for (data *queryPoint : *testData)
    {
        findKNearest(queryPoint);
        int prediction = predict();
        if(prediction == queryPoint->getLabel())
            count++;
        dataIndex++;
        //std::cout << "Current Performance = " << std::fixed << std::setprecision(3) << ((double) count * 100)/((double) dataIndex) << '\n';
    }
    std::cout << "Tested Performance = " << std::fixed << std::setprecision(3) << ((double) count * 100)/((double) testData->size()) << '\n';
    if (FILE.is_open())    
        FILE << "Tested Performance = " << std::fixed << std::setprecision(3) << ((double) count * 100)/((double) testData->size()) << '\n';
    FILE.close();
    return ((double) count * 100)/((double) testData->size());
} // prove model is repeatable (test data)