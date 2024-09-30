#ifndef COMMON_HPP
#define COMMON_HPP
#include "dataHandler.hpp"

class CommonData
{
    protected:
        std::vector<data *> * trainingData;
        std::vector<data *> * testData;
        std::vector<data *> * validationData;
    public:
        void setTrainingData(std::vector<data *> * vect);
        void setTestData(std::vector<data *> * vect);
        void setValidationData(std::vector<data *> * vect);
};

#endif