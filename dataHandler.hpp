#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP
#include <fstream>
#include "data.hpp"
#include <vector>
#include <cstdlib>
#include <string>
#include <map> // to map a class label to an enumerated value
#include <unordered_set> //

class DataHandler
{
    private:
        std::vector<data *> *dataArray; // all of the data pre-split
        std::vector<data *> *trainingData;
        std::vector<data *> *testData;
        std::vector<data *> *validationData;

        int numClasses;
        int featureVectorSize;
        std::map<uint8_t, int> classMap;
    
        const double TRAIN_SET_PERCENT = 0.75;
        const double TEST_SET_PERCENT = 0.2;
        const double VALIDATION_SET_PERCENT = 0.05;

        
    public:
        DataHandler();
        ~DataHandler();
        void readFeatureVector(std::string path);
        void readFeatureLabels(std::string path);
        void splitData();
        void countClasses();
        
        uint32_t convertToLittleEndian(const unsigned char* bytes);
        std::vector<data *> * getTrainingData();
        std::vector<data *> * getTestData();
        std::vector<data *> * getValidationData();
};

#endif