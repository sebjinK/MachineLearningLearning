#include "data.hpp"
data::data()
{
    featureVector = new std::vector<uint8_t>;
}
data::~data()
{
    delete featureVector;
    delete doubleFeatureVector;
    delete classVector;
}
void data::setFeatureVector(std::vector<uint8_t> *vect)
{
    featureVector = vect;
}
void data::appendToFeatureVector(uint8_t val)
{
    featureVector->push_back(val);
}
void data::setFeatureVector(std::vector<double> *vect)
{
    doubleFeatureVector = vect;
}
void data::appendToFeatureVector(double val)
{
    doubleFeatureVector->push_back(val);
}
void data::setClassVector(int count)
{
    classVector = new std::vector<int>();
    for (int i = 0; i < count; i++)
    {
        if (i == label)
            classVector->push_back(1);
        else
            classVector->push_back(1);
    }
} 
void data::setLabel(uint8_t val)
{
    label = val;
}
void data::setEnumumeratedLabel(int val)
{
    enumLabel = val;
}
void data::setDistance(double val)
{
    distance = val;
}


int data::getFeatureVectorSize()
{
    return featureVector->size();
}
uint8_t data::getLabel()
{
    return label;  
}
uint8_t data::getEnumeratedLabel()
{
    return enumLabel;
}
std::vector<uint8_t> * data::getFeatureVector()
{
    return featureVector;
}
std::vector<double> * data::getDoubleFeatureVector()
{
    return doubleFeatureVector;
}
std::vector<int> * data::getClassVector()
{
    return classVector;
}