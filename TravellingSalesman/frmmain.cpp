#include "frmmain.h"
#include "ui_frmmain.h"
#include <iterator.h>
#include <QVector2D>
#include <QDebug>

frmMain::frmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::frmMain)
{
    ui->setupUi(this);
    ui->verticalLayout->addWidget(&s);
    timer1->setInterval(10);
    connect(timer1, SIGNAL(timeout()),this,SLOT(oneTick()));
}

frmMain::~frmMain()
{
    delete ui;
}

void frmMain::on_btn_clearCities_clicked()
{
    if(running) {
        running = false;
        timer1->stop();
        ui->btn_start->setText("Start");
    }
    s.setIter(0);
    s.deleteCities();
    s.deleteVertices();
    s.resetIteration();
    s.resetAccuracyReaches();
    s.update();

}

void frmMain::on_btn_start_clicked()
{
    if (!running) {
        running = true;
        s.start = clock();
        timer1->start();
        ui->btn_start->setText("Stop");
    }
    else {
        running = false;
        s.end = clock();
        timer1->stop();
        ui->btn_start->setText("Start");
    }
    //qDebug () << s.getTime();
}

void frmMain::oneTick() {
    if (!s.getAccuracyReached()) {
        s.apply();
        s.update();
    }
    else {
        timer1->stop();
        s.end = clock();
        //qDebug() << s.getTime();
    }
}

void frmMain::on_pushButtonChange_clicked() //Update the values.
{
    s.setBeta(ui->doubleSpinBox_beta->value());
    s.setAlpha(ui->doubleSpinBox_alpha->value());
    s.setIter_max(ui->spinBox_iter->value());
    s.setK_zero(ui->doubleSpinBox_ko->value());
    s.setETAziel(ui->SpinBoxETA->value());
    s.setCVratio(ui->SpinBoxRatio->value());
    s.setRadius(ui->SpinBox_Radius->value());
    s.updateValues();
    s.update();
}

void frmMain::on_pushButton_clicked()
{
    if(running) {
        running = false;
        timer1->stop();
        ui->btn_start->setText("Start");
    }
    s.resetIteration();
    s.resetAccuracyReaches();
    s.setNetPosition();
    s.update();

    if(running) {
        running = false;
        timer1->stop();
        ui->btn_start->setText("Start");
    }

}
