#ifndef DATA_HPP
#define DATA_HPP
#include <vector>
#include "stdint.h"
#include "stdio.h"
#include <iostream>

class data
{
    private:    
        std::vector<uint8_t> * featureVector; // No class at end
        uint8_t label;
        int enumLabel; // A -> 1, B -> 2
        double distance;

    public:
        data();
        ~data();
        void setFeatureVector(std::vector<uint8_t> *);
        void appendToFeatureVector(uint8_t);
        void setLabel(uint8_t);
        void setEnumumeratedLabel(int);
        void setDistance(double);
        
        int getFeatureVectorSize();
        uint8_t getLabel();
        uint8_t getEnumeratedLabel();

        std::vector<uint8_t> * getFeatureVector();
};

#endif