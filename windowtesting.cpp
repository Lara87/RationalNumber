#include "windowtesting.h"
#include "ui_windowtesting.h"
#include <QFile>
#include <QDebug>//чтобы делать отладку
#include <QTextStream>//подключили класс для потоков
#include <QList>
#include <QRadioButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QIcon>
#include <QMouseEvent>


WindowTesting::WindowTesting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowTesting)
{
    ui->setupUi(this);
    parse(readFile());
    QGroupBox *grbBig=new QGroupBox();
    QVBoxLayout *qvb = new QVBoxLayout();

    for(int i=0; i<book.length(); i++)
    {
        QLabel *labelQuestion = new QLabel(book[i].question, this);

        QHBoxLayout *hbl=new QHBoxLayout();
        hbl->addWidget(book[i].setRadioButtonsList.button1);
        hbl->addWidget(book[i].setRadioButtonsList.button2);
        hbl->addWidget(book[i].setRadioButtonsList.button3);
        QGroupBox *grb = new QGroupBox();
        grb->setLayout(hbl);

        QVBoxLayout *vbl=new QVBoxLayout();
        vbl->addWidget(labelQuestion);
        vbl->addWidget(grb);
        QGroupBox *grbQuestAnswer= new QGroupBox();
        grbQuestAnswer->setLayout(vbl);

        qvb->addWidget(grbQuestAnswer);
    }
    grbBig->setLayout(qvb);

    ui->scrollArea->setWidget(grbBig);

    QIcon winIcon(":/icon/iconPic.jpg");
    this->setWindowIcon(winIcon);
}

WindowTesting::~WindowTesting()
{
    delete ui;
}

bool WindowTesting::writeResultRightAnswer(int a)//запись в файл % правильных ответов
{
    QString userName;
    userName=ui->lineEditUserName->text();
    userName=userName.remove(" ");
    if(testRegUserName(userName))
    {
        QFile fileTest(userName);
        if(fileTest.open(QIODevice::WriteOnly))
           {
                QTextStream stream (&fileTest);
                stream <<ui->lineEditUserName->text();
                stream << "\n"+QString::number(a)+"% правильных ответов";
                fileTest.close();
           }
    }
    else
    {
        QMessageBox messageError;
        messageError.setWindowTitle("Тестирование");
        messageError.setText("Неправильно введены имя и фамилия");
        messageError.setInformativeText("Введите имя и фамилию");
        messageError.setStandardButtons(QMessageBox::Ok);
        messageError.setButtonText(QMessageBox::Ok, "Закрыть");
        messageError.setIcon(QMessageBox::Information);
        messageError.exec();
    }
}

int WindowTesting::rightAnswer()//метод подсчета % правильных ответов
{
    int s=0;

    for(int i=0; i<book.length();i++)
    {
        if(checkRadioButton(book[i]))
        {
            s++;
        }
    }
    double a, b;
    a=book.length();
    a/=100;
    b=s/a;
    return b;//возвращает % правильных ответов
}

bool WindowTesting::checkRadioButton(TestQuestion a)//сверяем правильный ответ и нажатую кнопку с ответом
{
    if(a.setRadioButtonsList.button1->isChecked()&&a.answerIndex==0)
    {
        return true;
    }
    if(a.setRadioButtonsList.button2->isChecked()&&a.answerIndex==1)
    {
        return true;
    }
    if(a.setRadioButtonsList.button3->isChecked()&&a.answerIndex==2)
    {
        return true;
    }
    return false;
}

QString WindowTesting::readFile()//создали функцию для чтения и работы с файлом
{
   QFile fileQuest ("C:\\Qt\\QtProjects\\Kursovaya1\\questions.txt");//создали объект для файла QFile_название_путь с расширешением
   if (fileQuest.open(QIODevice::ReadOnly))  //открываем файл и только для чтения - флаг для открытия
   {
       QString textQuest;//создали строковый объект
       QTextStream stream (&fileQuest);//поток
       textQuest = stream.readAll();//здесь мы решаем как читать: полностью, построчно, посимвольно и преобразовали это в строку
       return textQuest;
   }
    fileQuest.close();
    return QString::number(0);//0 - код ошибки в виде строки
}

void WindowTesting::parse(QString que)//делим текст на части
{
    QList<QString> stringListQue;

    if(que=="0")
    {
        qDebug()<<"Ошибка чтения";
    }
    else
    {
        QList <QString> slist=que.split("+*****+");//разделили весь текст по блоку вопрос
        for(int i=0; i<slist.length();i++)
        {
            TestQuestion blokquestion;
            QList <QString> sslist=slist[i].split("+***+");//делим на вопрос, варианты и ответ
            blokquestion.question=sslist[0];
            qDebug()<<sslist;//в списке 3 объекта
            qDebug()<<"---------";
            sslist[1].remove("\n");
            sslist[1].remove("\r");
            sslist[1].remove(" ");
            QList <QString> answersList=sslist[1].split("+*+");

            SetRadioButtons setbutton;
            setbutton.button1 = new QRadioButton(answersList[0]);
            setbutton.button2 = new QRadioButton(answersList[1]);
            setbutton.button3 = new QRadioButton(answersList[2]);
            blokquestion.setRadioButtonsList=setbutton;
            sslist[2].remove("\n");
            sslist[2].remove("\r");
            sslist[2].remove(" ");
            blokquestion.answerIndex=sslist[2].toInt();
            book.append(blokquestion);
            qDebug()<<book[0].question;
        }
    }
}

void WindowTesting::closeEvent(QCloseEvent *event)
{
   QMessageBox messageExit;
    messageExit.setWindowTitle("Тестирование");
    messageExit.setText("Вы действительно хотите выйти?");
    messageExit.setIcon(QMessageBox::Question);
    messageExit.setStandardButtons(QMessageBox::Cancel|QMessageBox::Ok);
    messageExit.setDefaultButton(QMessageBox::Ok);
    messageExit.setButtonText(QMessageBox::Cancel, "Нет");
    messageExit.setButtonText(QMessageBox::Ok, "Да");
    int push =  messageExit.exec();//определяем, что было нажато
    switch (push)
    {
      case QMessageBox::Cancel:
           event->ignore();
           break;
      case QMessageBox::Ok:
           emit openMainWindow();//создали открытие предыдущего окна
           ui->lineEditUserName->setText(" ");
           break;
      default:
           break;
    }
}

void WindowTesting::on_pushButtonBack_clicked()
{
    if(this->close())
    {
       ui->lineEditUserName->setText(" ");
       emit openMainWindow();//создали открытие предыдущего окна
    }

}

void WindowTesting::on_pushButtonTestEnd_clicked()//по нажатию выводит % правильных ответов
{
    if(writeResultRightAnswer(rightAnswer()))
    {
        this->close();
    }
 }

bool WindowTesting::testRegUserName(QString fr)//функция для работы с регулярными выражениями
{
    QRegularExpression reg("^[\\D]{2,22}[\\s]?[\\D]{2,22}$");
    QRegularExpressionMatch match = reg.match(fr);//объект, кот хранит информацию о проверке на соответствие
    if (match.hasMatch())//соответствие найдено?
    {
        return true;
    }
    else return false;
}
