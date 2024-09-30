#include "data.hpp"
data::data()
{
    featureVector = new std::vector<uint8_t>;
}
data::~data()
{
    // FIXME
}
void data::setFeatureVector(std::vector<uint8_t> *vect)
{
    featureVector = vect;
}
void data::appendToFeatureVector(uint8_t val)
{
    featureVector->push_back(val);
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