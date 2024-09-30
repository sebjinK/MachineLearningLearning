#include "common.hpp"
void CommonData::setTrainingData(std::vector<data *> * vect)
{
    trainingData = vect;
}
void CommonData::setTestData(std::vector<data *> * vect)
{
    testData = vect;
}
void CommonData::setValidationData(std::vector<data *> * vect)
{
    validationData = vect;
}