#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>


#include "supertimer.h"
#include "templateclass.h"

namespace Ui {
class MainWindow;
}

class TestCbFunc
{
public:
    void cbFunc_test(){ qDebug()<<"TestCbFunc::cbFun_test() is called"<<endl;}
};
extern TestCbFunc G_testcbfunc;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void testTimeOut(QString test);
    void testTimeOutvoid();

    //typedef decltype(&MainWindow::testTimeOut)* PF;
    void mTimeOut(void(MainWindow::*pf)(QString ))
    {
        (this->*pf)("juest a test in MainWindow::mTimeOut");
    }

    void cbFunc_test(){ qDebug()<<"MainWindow::cbFun_test() is called"<<endl;}
private slots:
    void on_pushButton_nFun_clicked();

    void on_pushButton_TnFun_clicked();

    void on_pushButton_Tclass_clicked();

    void on_pushButton_ClearSuperTimer_clicked();

    void on_pushButton_setTimeOutNocb_clicked();

    void on_pushButton_setTimeOutAndcb_clicked();

    void on_pushButton_setTimeOutAndcb2_clicked();

    void on_pushButton_setIntervalNocb_clicked();

    void on_pushButton_setIntervalAndcb_clicked();

    void on_pushButton_setIntervalAndcb2_clicked();

private:
    Ui::MainWindow *ui;

    int spTimerID;

    TestCbFunc *mtestcbfunc;
};

#endif // MAINWINDOW_H
