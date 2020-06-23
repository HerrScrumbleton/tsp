#ifndef TRAVELLINGSALESMAN_H
#define TRAVELLINGSALESMAN_H
#include <QVector>
#include <QVector2D>
#include <QWidget>
#include <QPoint>
#include <elasticnet.h>

class TravellingSalesman: public QWidget, public ElasticNet
{
    Q_OBJECT
public:
    explicit TravellingSalesman(QWidget *parent = nullptr);


private:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    int citySize = 4; //Size of a city.
    int vertexSize = 3; //Size of the net-vertices.

};

#endif // TRAVELLINGSALESMAN_H
