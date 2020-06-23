#ifndef ELASTICNET_H
#define ELASTICNET_H
#include <QVector2D>
#include <QVector>
#include <iterable.h>
#include <chrono>

class ElasticNet: public Iterable
{
public:
    ElasticNet();
    QVector<QVector2D> cities;
    QVector<QVector2D> vertices;
    QVector<bool> accuracy_list;
    clock_t start;
    clock_t end;

    void updateValues();
    void addCity(int,int);
    void deleteCities();

    void addVertex();
    void deleteVertices();
    void setNetPosition();

    void apply() override;
    double getTemperatur();
    void resetIteration();

    void setRadius(int);
    int getRadius();

    void setCVratio(double);
    double getCVratio();

    void setETAziel(double);
    double getETAziel();


    bool getAccuracyReached();
    void resetAccuracyReaches();

    double getTime();

    void setIter_max(int);
    void setIter(int);

    void setAlpha(double);
    void setBeta(double);

    void setK_zero(double);



private:
    int radiusNet = 45;
    double CV_ratio = 2.5;
    double ETA_ziel = 1/200;
    double alpha = 1;
    double beta = 1;
    double K_zero = 0.1;
    int Iter_max = 1000;
    int iterationNumber = 0;
    bool accuracy_reached = false;

};

#endif // ELASTICNET_H
