#include "elasticnet.h"
#include <QDebug>
#include <math.h>

ElasticNet::ElasticNet()
{

}

void ElasticNet::updateValues() { //Add and remove vertices to match CV_ratio. Repositions the net afterwards.
    if (static_cast<double>(vertices.length())/static_cast<double>(cities.length()) < CV_ratio) {
        while(static_cast<double>(vertices.length())/static_cast<double>(cities.length()) < CV_ratio) {
            addVertex();
        }
    }
    else {
        while(static_cast<double>(vertices.length())/static_cast<double>(cities.length()) > CV_ratio) {
            vertices.remove(vertices.length()-1);
            accuracy_list.remove(accuracy_list.length()-1);
        }
    }
    setNetPosition();


}
void ElasticNet::addCity(int x, int y) { //Adds a new city.
    cities.append(QVector2D(x, y));
    while(static_cast<double>(vertices.length())/static_cast<double>(cities.length()) < CV_ratio) {
        addVertex();
    }
    for (int var = 0; var < accuracy_list.length(); ++var) {
        accuracy_list[var] = false;
    }
    setNetPosition();

}

void ElasticNet::deleteCities() { //Deletes all cities.
    cities.clear();
}

void ElasticNet::addVertex() { //Add a vertice.
    vertices.append(QVector2D(0,0));
    accuracy_list.append(false);

}

void ElasticNet::deleteVertices() { //Deletes all vertices.
    vertices.clear();
    accuracy_list.clear();
}

void ElasticNet::setNetPosition() { //Set the position for the vertices.
    double centerX = 0;
    double centerY = 0;

    for(int i = 0; i < cities.length(); i++) {
        centerX = centerX + static_cast<double>(cities[i].x());
        centerY = centerY + static_cast<double>(cities[i].y());
    }

    centerX = centerX/cities.length();
    centerY = centerY/cities.length();

    for(int k = 0; k < vertices.length(); k++) {
        vertices[k].setX(static_cast<float>(centerX + radiusNet*cos(2*M_PI*k/static_cast<double>(vertices.length()))));
        vertices[k].setY(static_cast<float>(centerY + radiusNet*sin(2*M_PI*k/static_cast<double>(vertices.length()))));
    }

    for (int var = 0; var < accuracy_list.length(); ++var) {
        accuracy_list[var] = false;
    }
}

double ElasticNet::getETAziel() {
    return ETA_ziel;

}

void ElasticNet::setRadius(int y) {
    radiusNet = y;
}

int ElasticNet::getRadius() {
    return radiusNet;
}
void ElasticNet::setETAziel(double x) {
    ETA_ziel = x;
}

void ElasticNet::setCVratio(double y) {
    CV_ratio = y;
}

double ElasticNet::getCVratio() {
    return CV_ratio;
}

double ElasticNet::getTemperatur() { //Calculates the Temperature.
    double K = fmax(0.01,K_zero*pow(0.99,floor(static_cast<double>(iterationNumber)/50)));
    return 2*pow(K,2);
}

void ElasticNet::apply() {
    QVector<QVector2D> vertices1 = vertices;
    QVector<QVector<double>> influence; //Stores the influence  of all cities to each vertice of the net.
    QVector<double> emptyVector;

    for (int x = 0; x < vertices.length(); x++) { //Initialize influence.
        influence.append(emptyVector);
        for(int i = 0; i < cities.length(); i++) {
            influence[x].append(0);
        }
    }


    for(int a = 0; a < vertices.length(); a++) { //Calculate the influences.
        if (!accuracy_list[0]) {
            for(int i = 0; i < cities.length(); i++) {
                double exponent = pow(static_cast<double>((cities[i]-vertices[a]).length()),2)/getTemperatur();
                double sum = 0;
                for(int alpha_s = 0; alpha_s < vertices.length(); alpha_s++) {
                    double x = exponent-pow(static_cast<double>((cities[i]-vertices[alpha_s]).length()),2)/getTemperatur();
                    sum = sum + pow(M_E,x);
                }
                influence[a][i] = 1/sum;
            }
        }
    }

    for(int a = 0; a < vertices.length(); a++) { //Calculate delta y.
        if (!accuracy_list[a]) {
            QVector2D delta_y;
            bool breaker = true;
            for(int i = 0; i < cities.length(); i++) {
                if (static_cast<double>((cities[i]-vertices[a]).length()) <= ETA_ziel) {
                    breaker = false;
                }
                delta_y = delta_y + static_cast<float>(influence[a][i])*(cities[i]-vertices[a]);
            }

            delta_y = delta_y * static_cast<float>(alpha);

            int z = (a-1)%vertices.length(); //Fixes the weird modulo interaction for negative values.
            if (z < 0) {
                z = vertices1.length()-1;
            }

            delta_y = delta_y + static_cast<float>(beta*sqrt(getTemperatur()/2))*(vertices[z]-2*vertices[a]+vertices[(a+1)%vertices.length()]);

            if (breaker) {
                vertices1[a] = vertices1[a] + delta_y;
            }
        }
    }
    vertices = vertices1;

    double eta_n = 0;

    for (int i = 0; i < cities.length(); i++) {
        double eta_temp = 0;
        int verticenumber = 0;
        for ( int a = 0; a < vertices.length(); a++) {
            if (eta_temp == 0 or eta_temp > static_cast<double>((cities[i]-vertices[a]).length())) {
                eta_temp = static_cast<double>((cities[i]-vertices[a]).length());
                verticenumber = a;
            }
        }
        if (!accuracy_list[verticenumber]) {
            accuracy_list[verticenumber] = true;
        }
        if (eta_n < eta_temp) {
            eta_n = eta_temp;
        }
    }
    //qDebug() << "Genauigkeitsliste " << accuracy_list;
    if (eta_n < ETA_ziel) {
        qDebug() << "Genauigkeitskriterium ist erreicht";
        accuracy_reached = true;
    }
    iterationNumber++;
    //qDebug() << iterationNumber;
    if (iterationNumber == Iter_max) {
        qDebug () << "Max iter ist erreicht";
        accuracy_reached = true;
    }
}

void ElasticNet::resetIteration() {
    iterationNumber = 0;
}

bool ElasticNet::getAccuracyReached() {
    return accuracy_reached;
}

void ElasticNet::resetAccuracyReaches()
{
    accuracy_reached = false;
}


double ElasticNet::getTime()
{
    clock_t clockTicksTaken = end - start;
    double time = clockTicksTaken / static_cast<double>(CLOCKS_PER_SEC);

    return time;
}

void ElasticNet::setBeta(double beta_set) {
    beta = beta_set;
}

void ElasticNet::setK_zero(double setK_zero)
{
    K_zero = setK_zero;
}

void ElasticNet::setAlpha(double alpha_set) {
    alpha = alpha_set;
}

void ElasticNet::setIter_max(int iter_max_set) {
    Iter_max = iter_max_set;
}

void ElasticNet::setIter(int iter_set) {
    iterationNumber = iter_set;
}
