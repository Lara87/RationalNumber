#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QRegExp"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    windowT = new WindowTeoriya();//выделили память под новый объект
    connect (windowT, &WindowTeoriya::openMainWindow, this, &MainWindow::show);//подключили сигнал
              //кто,        что            -       этот объект - метод
    windowP = new WindowPresentation();
    connect (windowP, &WindowPresentation::openMainWindow, this, &MainWindow::show);

    kursT= new KursTitle();
    connect(kursT, &KursTitle::openMainWindow, this, &MainWindow::show);
    kursT->show();

    windowTs = new WindowTesting();
    connect (windowTs, &WindowTesting::openMainWindow, this, &MainWindow::show);

    QIcon winIcon(":/icon/iconPic.jpg");
    this->setWindowIcon(winIcon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonTeoriya_clicked()
{
    windowT->show();//открытие окна - показ
    this->close();//закрыли объект в котором находимся
}


void MainWindow::on_pushButtonExit_clicked()
{
    this->close();
}

void MainWindow::on_pushButtonDemo_clicked()
{
    windowP->show();
    this->close();
}

void MainWindow::on_pushButtonTesting_clicked()
{
    windowTs->show();
    this->close();
}

