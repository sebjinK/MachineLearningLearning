#include "kmeans.hpp"

KMeans::KMeans(int k)
{
    numClusters = k;
    clusters = new std::vector<cluster_t *>;
    usedIndexes = new std::unordered_set<int>;

}
KMeans::~KMeans()
{
    //nothing to do
    for (auto c : *clusters)
    {
        delete c;
    }
    delete clusters;
    delete usedIndexes;
}

void KMeans::initClusters()
{
    for (int i = 0; i < numClusters; i++)
    {
        int index = (rand() % trainingData->size());
        while(usedIndexes->find(index) != usedIndexes->end())
        {
            index = (rand() % trainingData->size());
        }
        clusters->push_back(new cluster(trainingData->at(index)));
        usedIndexes->insert(index);
    }
}
void KMeans::initClustersForEachClass()
{
    std::unordered_set<int> classesUsed;
    for (int i = 0; i < trainingData->size(); i++)
    {
        if (classesUsed.find(trainingData->at(i)->getLabel()) == classesUsed.end())
        {
            clusters->push_back(new cluster_t(trainingData->at(i)));
            classesUsed.insert(trainingData->at(i)->getLabel());
            usedIndexes->insert(i); // avoid duplicated data
        }
    }
}
void KMeans::train()
{
    int index = 0;
    while (usedIndexes->size() < trainingData->size())
    {
        while(usedIndexes->find(index) != usedIndexes->end())
        {
            index++;
        }
        double minDistance = std::numeric_limits<double>::max();
        int bestCluster = 0;
        for (int j = 0; j < clusters->size(); j++)
        {
            double currentDistance = euclideanDistance(clusters->at(j)->centroid, trainingData->at(index));
            if (currentDistance < minDistance)
            {
                minDistance = currentDistance;
                bestCluster = j;
            }
        }    
        clusters->at(bestCluster)->addToCluster(trainingData->at(index));
        usedIndexes->insert(index);
    }
}
double KMeans::euclideanDistance(std::vector<double> * centroid, data * point)
{
    double distance = 0.0;
    for (int i = 0; i < centroid->size(); i++)
    {
        distance += pow(centroid->at(i) - point->getFeatureVector()->at(i), 2);
    }
    return sqrt(distance);
    
}
double KMeans::validate()
{
    double numCorrect = 0.0;
    for (auto queryPoint : *validationData)
    {
        double minDistance = std::numeric_limits<double>::max();
        int bestCluster = 0;
        for (int j = 0; j < clusters->size(); j++)
        {
            double currentDistance = euclideanDistance(clusters->at(j)->centroid, queryPoint);
            if (currentDistance < minDistance)
            {
                minDistance = currentDistance;
                bestCluster = j;
            }
        }    
        if (clusters->at(bestCluster)->mostFrequentClass == queryPoint->getLabel())
            numCorrect++;   
    }
    return 100.0 * (numCorrect / (double)validationData->size());
    
}    
double KMeans::test()
{
    double numCorrect = 0.0;
    for (auto queryPoint : *testData)
    {
        double minDistance = std::numeric_limits<double>::max();
        int bestCluster = 0;
        for (int j = 0; j < clusters->size(); j++)
        {
            double currentDistance = euclideanDistance(clusters->at(j)->centroid, queryPoint);
            if (currentDistance < minDistance)
            {
                minDistance = currentDistance;
                bestCluster = j;
            }
        }    
        if (clusters->at(bestCluster)->mostFrequentClass == queryPoint->getLabel())
            numCorrect++;   
    }
    return 100.0 * (numCorrect / (double)testData->size());
}