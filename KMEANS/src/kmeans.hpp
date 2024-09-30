#ifndef KMEANS_HPP
#define KMEANS_HPP
#include "../../src/common.hpp"
/*
 we're using limits, cstdlib, cmath, maps, and what's in dataHandler.o
*/


typedef struct cluster
{
    //contains four fields: 
        // centroid of type vector<double>
        // cluster points of type vector<data*>
        // map counts classes within cluster
        // int that captures most frequent class within the cluster

        // methods constructor
        // setMostFrequentClass();

    std::vector<double> * centroid;
    std::vector<data*> * clusterPoints;
    std::map<int, int> classCounts;
    int mostFrequentClass;
    cluster(data * initialPoint)
    {
        centroid = new std::vector<double>;
        clusterPoints = new std::vector<data*>;
        for (auto value : *(initialPoint->getFeatureVector()))
        {
            centroid->push_back(value); // initiallizing each centroid with the value of the first data point
        }
        clusterPoints->push_back(initialPoint);
        classCounts[initialPoint->getLabel()] = 1;
        mostFrequentClass = initialPoint->getLabel();
    }
    void addToCluster(data* point)
    {
        // update the running avg of each centroid value
        // keep track prev size of cluster
        // add the new point to that cluster
        // calcluate running avg
            // mult i by prev_size
            // add that point at(i) to value
            /// div value by the number of points in the cluster
            // readd the value to the centroid

        int prevSize = clusterPoints->size();
        clusterPoints->push_back(point);
        for (int i = 0; i <  centroid->size() - 1; i++) // go up to the size minus one since we are adding the new point to the value
        {
            double value = centroid->at(i);
            value *= prevSize;
            value += point->getFeatureVector()->at(i);
            value /= (double) clusterPoints->size();
            centroid->at(i) = value;
        }
        if (classCounts.find(point->getLabel()) == classCounts.end())
            classCounts[point->getLabel()] = 1;
        else
            classCounts[point->getLabel()]++;
        setMostFrequentClass();
    }
    void setMostFrequentClass()
    {
        int bestClass;
        int frequency;
        for (auto kv : classCounts)
        {
            if(kv.second > frequency)
            {
                frequency = kv.second;
                bestClass = kv.first;
            }
        }
        mostFrequentClass = bestClass;
    }
} cluster_t;

class KMeans : public CommonData
{
    // num of clusters
    // vector<cluster> numOfClustersInModel
    // unordered set which allows us to keep which values of our training data we have used 
    // constructor that takes a value k
    // void that allows us to init clusters and create a new cluster with that data point
    // initialized cluster with aeach class
    // it might make sense to have the number of clusters be equal to the number of clusters in the class
    private:
        int numClusters;
        std::vector <cluster *> * clusters;
        std::unordered_set<int> * usedIndexes;

    public:
        KMeans(int k);
        ~KMeans();
        void initClusters();
        void initClustersForEachClass();
        void train();
        double euclideanDistance(std::vector<double> *, data *);
        double validate();
        double test();
};




#endif