#include "./KNN/src/knn.hpp"
#include "./KMEANS/src/kmeans.hpp"

int main()
{
    srand(time(0));
    DataHandler * dh = new DataHandler();
    dh->readFeatureVector("./images&labels/t10k-images.idx3-ubyte");// read from MNIST
    dh->readFeatureLabels("./images&labels/t10k-labels.idx1-ubyte"); //read from MNIST
    //srand(time(0));
    dh->splitData();
    dh->countClasses();

    double performance = 0.0;
    double bestPerforamce = 0.0;
    int bestK = 1;
    for (int k = dh->getClassCounts(); k < dh->getTrainingData()->size(); k++)
    {
        KMeans * km = new KMeans(k);
        km->setTrainingData(dh->getTrainingData());
        km->setTestData(dh->getTestData());
        km->setValidationData(dh->getValidationData());
        km->initClusters();
        km->train();
        performance = km->validate();
        std::cout << "Current Perforamnce @ K = " << k << ": " << std::fixed << std::setprecision(2) << performance << '\n';
        if (performance > bestPerforamce)
        {
            bestPerforamce = performance;
            bestK = k;
        } 
    }
    KMeans * km = new KMeans(bestK);
    km->setTrainingData(dh->getTrainingData());
    km->setTestData(dh->getTestData());
    km->setValidationData(dh->getValidationData());
    km->initClusters();
    performance = km->test();
    std::cout << "Tested Perforamnce @ K = " << bestK << ": " << std::fixed << std::setprecision(2) << performance << '\n';


    
    KNN * knearest = new KNN();
    knearest->setTrainingData(dh->getTrainingData());
    knearest->setTestData(dh->getTestData());
    knearest->setValidationData(dh->getValidationData());
    performance = 0;
    double bestPerformance = 0;
    bestK = 1;
    for (int i = 1; i <= 4; i++)
    {
        if (i == 1)
        {
            knearest->setK(i);
            performance = knearest->validatePerformance();
            bestPerformance = performance;
        }
        else
        {
            knearest->setK(i);
            performance = knearest->validatePerformance();
            if (performance > bestPerformance)
            {
                bestPerformance = performance;
                bestK = i;
            }
        }
    }
    knearest->setK(bestK);
    knearest->testPerformance();
}