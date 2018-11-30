#include "mainwindow.h"
#include "ui_mainwindow.h"


//模板函数基本用法-----------------------------------------------------------------------
typedef decltype(&MainWindow::testTimeOut) PF2;//void (MainWindow::*pf)(QString)
template <typename T>
void TimeOut2( T * temp, void (T::*pf)(QString) )
{
    (temp->*pf)("just a test in TimeOut2");
}

TestCbFunc G_testcbfunc;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    spTimerID = 0;
    mtestcbfunc = new TestCbFunc;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testTimeOut(QString test)
{
    qDebug()<<"MainWindow::testTimeOut() is called:->"<<endl;
    qDebug()<<test<<endl;
}

void MainWindow::testTimeOutvoid()
{
    qDebug()<<"MainWindow::testTimeOutvoid() is called"<<endl;
}

void MainWindow::on_pushButton_nFun_clicked()
{
    mTimeOut(&MainWindow::testTimeOut);
}

void MainWindow::on_pushButton_TnFun_clicked()
{
    TimeOut2(this, &MainWindow::testTimeOut );
}

void MainWindow::on_pushButton_Tclass_clicked()
{
    //test TEMPLATECLASS
    Compare<int > cmp1(3,7);  //定义对象cmp1，用于两个整数的比较
    cout<<cmp1.max( )<<" is the Maximum of two integer numbers."<<endl;
    cout<<cmp1.min( )<<" is the Minimum of two integer numbers."<<endl<<endl;
    Compare<float > cmp2(45.78,93.6);  //定义对象cmp2，用于两个浮点数的比较
    cout<<cmp2.max( )<<" is the Maximum of two float numbers."<<endl;
    cout<<cmp2.min( )<<" is the Minimum of two float numbers."<<endl<<endl;
    Compare<char> cmp3('a','A');  //定义对象cmp3，用于两个字符的比较
    cout<<cmp3.max( )<<" is the Maximum of two characters."<<endl;
    cout<<cmp3.min( )<<" is the Minimum of two characters."<<endl;
}

void MainWindow::on_pushButton_ClearSuperTimer_clicked()
{
    qDebug()<<"ClearTimerID:"<<spTimerID<<endl;
    SpTimer.ClearTimer(spTimerID);
}

void MainWindow::on_pushButton_setTimeOutNocb_clicked()
{
    spTimerID = SpTimer.setTimeOut(this, &MainWindow::testTimeOutvoid, 2000);//不带回调函数
    qDebug()<<"do something, no cbfunc setTimeOut spTimerID:"<<spTimerID<<endl;
}

void MainWindow::on_pushButton_setTimeOutAndcb_clicked()
{
    spTimerID = SpTimer.setTimeOut(this, &MainWindow::testTimeOutvoid, 2000, this, &MainWindow::cbFunc_test);//带回调函数
    qDebug()<<"do something, spTimerID:"<<spTimerID<<endl;
}

void MainWindow::on_pushButton_setTimeOutAndcb2_clicked()
{
    spTimerID = SpTimer.setTimeOut(this, &MainWindow::testTimeOutvoid, 2000, &G_testcbfunc, &TestCbFunc::cbFunc_test);//带不同对象的回调函数
    qDebug()<<"do something, spTimerID:"<<spTimerID<<endl;
}

void MainWindow::on_pushButton_setIntervalNocb_clicked()
{
    spTimerID = SpTimer.setInterval(this, &MainWindow::testTimeOutvoid, 1000);//不带回调函数
    qDebug()<<"do something, no cbfunc setInterval spTimerID:"<<spTimerID<<endl;
}

void MainWindow::on_pushButton_setIntervalAndcb_clicked()
{
    spTimerID = SpTimer.setInterval(this, &MainWindow::testTimeOutvoid, 1000, mtestcbfunc, &TestCbFunc::cbFunc_test);//带不同对象的回调函数
    qDebug()<<"do something, spTimerID:"<<spTimerID<<endl;
}

void MainWindow::on_pushButton_setIntervalAndcb2_clicked()
{
    spTimerID = SpTimer.setInterval(mtestcbfunc, &TestCbFunc::cbFunc_test, 1000, &G_testcbfunc, &TestCbFunc::cbFunc_test);//带不同对象的回调函数
    qDebug()<<"do something, spTimerID:"<<spTimerID<<endl;
}
