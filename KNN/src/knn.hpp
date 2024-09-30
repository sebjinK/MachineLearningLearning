#ifndef KNN_H
#define KNN_H
#include <vector>
#include "../../src/dataHandler.hpp"

class KNN
{
    private:
        int k;
        std::vector<data *> * neighbors;
        std::vector<data *> * trainingData;
        std::vector<data *> * testData;
        std::vector<data *> * validationData;

    public:
        KNN(int);
        KNN();
        ~KNN();
        void findKNearest(data *queryPoint);
        void setTrainingData(std::vector<data *> * vect);
        void setTestData(std::vector<data *> * vect);
        void setValidationData(std::vector<data *> * vect);
        void setK(int val);

        int predict(); // return the predicted class
        double calculateDistance(data * queryPoint, data * input); // calculate using euclidean distance but also make a placeholder to learn manhatten disantces
        double validatePerformance(); //Pick correct K value (validation data)
        double testPerformance(); // prove model is repeatable (test data)

};

#endif