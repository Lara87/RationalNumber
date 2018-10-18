#include "windowteoriya.h"
#include "ui_windowteoriya.h"
#include <QFile>
#include <QDebug>//чтобы делать отладку
#include <QTextStream>//подключили класс для потоков
#include <QList>

WindowTeoriya::WindowTeoriya(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowTeoriya)
{
    ui->setupUi(this);
    book=parse(loadFile());
    bookIndex=0;
    ui->textEditRead->setText(book[bookIndex]);

    QIcon winIcon(":/icon/iconPic.jpg");
    this->setWindowIcon(winIcon);
}

QString WindowTeoriya::loadFile()//создали функцию для чтения и работы с файлом
{
    QFile file ("C:\\Qt\\QtProjects\\Kursovaya1\\Rational2.html");//создали объект для файла QFile_название_путь с расширешением
   if (file.open(QIODevice::ReadOnly))  //открываем файл и только для чтения - флаг для открытия
   {
       QString text;//создали строковый объект
       QTextStream stream (&file);//поток
       text = stream.readAll();//здесь мы решаем как читать: полностью, построчно, посимвольно и преобразовали это в строку
       return text;
   }
    file.close();
    return QString::number(0);//0 - код ошибки в виде строки
}

QList <QString> WindowTeoriya::parse(QString s)//делим текст на части
{
    QList<QString> stringList;
    if(s=="0")
    {
        qDebug()<<"Ошибка чтения";
    }
    else
    {
        stringList=s.split("*****^*****");
    }
    return stringList;
}

WindowTeoriya::~WindowTeoriya()
{
    delete ui;
}

void WindowTeoriya::on_pushButtonBack_clicked()
{
    this->close();
    emit openMainWindow();//создали открытие предыдущего окна
}

void WindowTeoriya::on_pushButtonNext_clicked()
{
    if(bookIndex<(book.length()-1))
    {
        bookIndex++;
        ui->textEditRead->setText(book[bookIndex]);
        ui->textEditRead->setStyleSheet(QString::fromUtf8("background-color: rgb(206, 205, 213); font-family: Verdana"));
    }
}

void WindowTeoriya::on_pushButtonPrev_clicked()
{
    if(bookIndex>0)
    {
        bookIndex--;
        ui->textEditRead->setText(book[bookIndex]);
        ui->textEditRead->setStyleSheet(QString::fromUtf8("background-color: rgb(206, 205, 213);  font-family: Verdana"));
    }
}
