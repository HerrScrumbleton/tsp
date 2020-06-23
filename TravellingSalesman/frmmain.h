#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QMainWindow>
#include <travellingsalesman.h>
#include <iterator.h>
#include <QTimer>

namespace Ui {
class frmMain;
}

class frmMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = nullptr);
    ~frmMain();

private slots:
    void on_btn_clearCities_clicked();
    void on_btn_start_clicked();
    void oneTick();
    void on_pushButtonChange_clicked();

    void on_pushButton_clicked();

private:
    Ui::frmMain *ui;
    TravellingSalesman s;
    Iterator iter = Iterator();
    QTimer* timer1 = new QTimer(this);
    bool running = false;

};

#endif // FRMMAIN_H
