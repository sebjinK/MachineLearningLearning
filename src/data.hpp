#ifndef DATA_HPP
#define DATA_HPP
#include <vector>
#include "stdint.h"
#include "stdio.h"
#include <iostream>

class data
{
    private:    
        std::vector<uint8_t> * featureVector; // Set up the feature vector array to take in the image binary
        std::vector<double> * doubleFeatureVector;
        std::vector<int> * classVector;
        uint8_t label; // take in each label temporarily
        int enumLabel; // A -> 1, B -> 2
        double distance; // take in distance of how far apart using knn

    public:
        data();
        ~data();
        void setFeatureVector(std::vector<uint8_t> *vect); 
        void appendToFeatureVector(uint8_t val);
        void setFeatureVector(std::vector<double> *vect); 
        void appendToFeatureVector(double val);
        void setClassVector(int count); 
        void setLabel(uint8_t);
        void setEnumumeratedLabel(int);
        void setDistance(double);
        
        int getFeatureVectorSize(); 
        uint8_t getLabel();
        uint8_t getEnumeratedLabel();

        std::vector<uint8_t> * getFeatureVector();
        std::vector<double> * getDoubleFeatureVector();
        std::vector<int> * getClassVector();
        double getDistancce();
};

#endif