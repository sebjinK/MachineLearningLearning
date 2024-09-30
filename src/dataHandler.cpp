#include "dataHandler.hpp"
DataHandler::DataHandler()
{
    dataArray = new std::vector<data*>;  // these are all set to data since this is the data handler
    testData = new std::vector<data*>;
    trainingData = new std::vector<data*>;
    validationData = new std::vector<data*>;
}
DataHandler::~DataHandler()
{
    //FREE Dynamically Allocated stuff
}
void DataHandler::readFeatureVector(std::string path)
{
    uint32_t header[4]; // |MAGIC|NUM IMAGES|ROWSIZE|COLUMNSIZE 32 byes each
    unsigned char bytes[4];
    FILE *f = fopen(path.c_str(), "rb"); // we want to be able to read in
    if (!f)
    {
        std::cerr << "Could not find file!\n";
        exit(1);
    }
    for (int i = 0; i < 4; i++)
    {
        if (fread(bytes, sizeof(bytes), 1, f))
        {
            header[i] = convertToLittleEndian(bytes);
        }
    }
    std::cout << "Done getting Input File Header.\n"; 
    int imageSize = header[2] * header[3];
    for (int i = 0; i < header[1]; i++)
    {
        data* d = new data();
        uint8_t element[1];
        for (int j = 0; j < imageSize; j++)
        {
            if (fread(element, sizeof(element), 1, f))
            {
                d->appendToFeatureVector(element[0]);
            }
            else
            {
                std::cerr << "Error reading file!\n";
                exit(1);
            }
        }
        dataArray->push_back(d);
    }
    std::cout << "Successfully read and stored " << dataArray->size() << " feature vectors\n";


}
void DataHandler::readFeatureLabels(std::string path)
{
    uint32_t header[2]; // |MAGIC|NUM IMAGES|ROWSIZE|COLUMNSIZE
    unsigned char bytes[4];
    FILE *f = fopen(path.c_str(), "rb");
    if (!f)
    {
        std::cerr << "Could not find file!\n" ; 
        exit(1);
    }
    for (int i = 0; i < 2; i++)
    {
        if (fread(bytes, sizeof(bytes), 1, f))
        {
            header[i] = convertToLittleEndian(bytes);
        }
    }
    std::cout << "Done getting Label File Header!\n";
    for (int i = 0; i < header[1]; i++)
    {
        uint8_t element[1];
        if (!fread(element, sizeof(element), 1, f))
        {
            std::cerr << "Error reading file!\n";
            exit(1);

        }
        dataArray->at(i)->setLabel(element[0]);
    }
    std::cout << "Successfully read and stored " << dataArray->size() << " feature labels\n";
}
void DataHandler::splitData()
{
    std::unordered_set<int> usedIndexes;
    int trainSize = dataArray->size() * TRAIN_SET_PERCENT;
    int testSize = dataArray->size() * TEST_SET_PERCENT;
    int validationSize = dataArray->size() * VALIDATION_SET_PERCENT;

    // Training Data
    int count = 0;
    std::cout << std::endl;
    while (count < trainSize)
    {
        int randIndex = rand() % dataArray->size(); // 0 & dataArray->size() - 1 
        if (usedIndexes.find(randIndex) == usedIndexes.end())
        {
            trainingData->push_back(dataArray->at(randIndex));
            usedIndexes.insert(randIndex);
            count++;
        }
        // std::cout << count << '\n';
    }
    std::cout << "Training data size: " << trainingData->size() << '\n';
    // Testing Data
    count = 0;
    while (count < testSize)
    {
        int randIndex = rand() % dataArray->size(); // 0 & dataArray->size() - 1 
        if (usedIndexes.find(randIndex) == usedIndexes.end())
        {
            testData->push_back(dataArray->at(randIndex));
            usedIndexes.insert(randIndex);
            count++;
        }
        //std::cout << count << '\n';
    }   
    std::cout << "Test data size: " << testData->size() << '\n'; 
    // Validation Data
    count = 0;
    while (count < validationSize)
    {
        int randIndex = rand() % dataArray->size(); // 0 & dataArray->size() - 1 
        if (usedIndexes.find(randIndex) == usedIndexes.end())
        {
            validationData->push_back(dataArray->at(randIndex));
            usedIndexes.insert(randIndex);
            count++;
        }
        // std::cout << count << '\n';
    }   
    std::cout << "Validation data size: " << validationData->size() << '\n'; 
}
void DataHandler::countClasses()
{
    int count = 0;
    for (unsigned i = 0; i < dataArray->size(); i++)
    {
        if (classMap.find(dataArray->at(i)->getLabel()) == classMap.end()) // Label isn't in the map
        {
            classMap[dataArray->at(i)->getLabel()] = count;
            dataArray->at(i)->setEnumumeratedLabel(count);
            count++;
        }
    }
    numClasses = count;
    std::cout << "Succcessdfully Extracted " << numClasses << " Unique Classes\n";
}
int DataHandler::getClassCounts()
{
    return numClasses;
}
uint32_t DataHandler::convertToLittleEndian(const unsigned char* bytes)
{
    return (uint32_t) ((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | (bytes[3])); // bytes[0 becomes the last bytes, bytes[1] becomes second to last, bytes[2] becomes third to last, bytes[3] becomes last
}
std::vector<data *> * DataHandler::getTrainingData()
{
    return trainingData;
}
std::vector<data *> * DataHandler::getTestData()
{
    return testData;
}
std::vector<data *> * DataHandler::getValidationData()
{
    return validationData;
}