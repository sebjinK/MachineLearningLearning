#ifndef KNN_H
#define KNN_H
#include "../../src/common.hpp"
#include <cmath>
#include <limits>
#include <iomanip>

class KNN : public CommonData // inherits the traingin data, test data and validation data from common.hpp
{
    private:
        int k;
        std::vector<data *> * neighbors;

    public:
        KNN(int);
        KNN();
        ~KNN();
        void findKNearest(data *queryPoint);
        void setK(int val);

        int predict(); // return the predicted class
        double calculateDistance(data * queryPoint, data * input); // calculate using euclidean distance but also make a placeholder to learn manhatten disantces
        double validatePerformance(); //Pick correct K value (validation data)
        double testPerformance(); // prove model is repeatable (test data)

};

#endif