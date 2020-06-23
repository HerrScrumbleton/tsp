#include "travellingsalesman.h"
#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QMouseEvent>
#include <QPoint>


TravellingSalesman::TravellingSalesman(QWidget *parent) : QWidget(parent)
{


}

void TravellingSalesman::paintEvent(QPaintEvent *) { //Paints the board.
    QPainter painter(this);
    painter.drawRect(0,0,width()-1,height()-1); //Draws the border of the widget.
    painter.setBrush(Qt::green);

    for(int i = 0; i < cities.length(); i++) { //Draw the cities.
        QPoint center = QPoint(static_cast<int>(cities[i].x()),static_cast<int>(cities[i].y()));
        painter.drawEllipse(center,citySize,citySize);
    }

    painter.setBrush(Qt::red);
    for(int j = 0; j < vertices.length(); j++) { //Draw the net.
        QPoint center = QPoint(static_cast<int>(vertices[j].x()),static_cast<int>(vertices[j].y()));
        painter.drawEllipse(center,vertexSize,vertexSize);
    }

    painter.setBrush(Qt::black);
    QPoint vertex1;
    QPoint vertex2;

    for(int k = 0; k < vertices.length(); k++) { //Draw the connections between two vertices.
        vertex1 = QPoint(static_cast<int>(vertices[k].x()),static_cast<int>(vertices[k].y()));
        if(k == vertices.length()-1) {
            vertex2 = QPoint(static_cast<int>(vertices[0].x()),static_cast<int>(vertices[0].y()));
        }
        else {
            vertex2 = QPoint(static_cast<int>(vertices[k+1].x()),static_cast<int>(vertices[k+1].y()));
        }
        painter.drawLine(vertex1,vertex2);

    }
}

void TravellingSalesman::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QVector2D CityLocation = QVector2D(event->pos().x(),event->pos().y());
        bool farEnough = true;
        for(int i = 0; i < cities.length(); i++) { //Make sure that the location is far enough away.
            if (cities[i].distanceToPoint(CityLocation) < static_cast<float>(2*getETAziel() +1)) {
                farEnough = false;
                break;
            }
        }
        if (farEnough) {
            addCity(event->pos().x(),event->pos().y());
        }
    }
    update();
}































