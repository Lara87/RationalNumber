#include "kurstitle.h"
#include "ui_kurstitle.h"
#include <QKeyEvent>
#include <QDebug>

KursTitle::KursTitle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KursTitle)
{
    ui->setupUi(this);

    QIcon winIcon(":/icon/iconPic.jpg");
    this->setWindowIcon(winIcon);
}

KursTitle::~KursTitle()
{
    delete ui;
}

void KursTitle::keyPressEvent(QKeyEvent *ev)
{
    switch (ev->key())
    {
        case Qt::Key_Return:
        {
            this->close();
            emit openMainWindow();
        }
        break;

        default:
             {
        qDebug()<<"ERORR";
             }
    }
}
