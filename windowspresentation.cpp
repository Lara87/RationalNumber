 #include "windowpresentation.h"
#include "ui_windowpresentation.h"
#include "QDebug"
#include "QRegExp"
#include <QString>
#include <QWebView>
#include <QList>

WindowPresentation::WindowPresentation(QWidget *parent) : QWidget(parent),ui(new Ui::WindowPresentation)
{
    ui->setupUi(this);

    ui->lineEditError->setVisible(false);//сообщение об ошибке- установить видимой - не показывается
    ui->lineEditError->setStyleSheet("QLineEdit { border: 0px; background-color: rgb(240, 240, 240) ; color: rgb(255, 0, 0);}");
    wV=new QWebView(this);
    wV->setGeometry(10, 190, 591, 181);
    wV->setHtml("");
    wV->show();

    QIcon winIcon(":/icon/iconPic.jpg");
    this->setWindowIcon(winIcon);

}

WindowPresentation::~WindowPresentation()
{
    delete ui;
}

void WindowPresentation::on_pushButtonBack1_clicked()//кнопка "назад"
{
    this->close();
    emit openMainWindow();//создаем открытие предыдущего окна
    ui->lineEditDecimal1->clear();
    ui->lineEditDecimal2->clear();
    ui->lineEditDenominator1->clear();
    ui->lineEditDenominator2->clear();
    ui->lineEditNumerator1->clear();
    ui->lineEditNumerator2->clear();
    ui->lineEditSign1->clear();
    ui->lineEditSign2->clear();
    ui->lineEditTotal1->clear();
    ui->lineEditTotal2->clear();
    ui->lineEditError->clear();
}

void WindowPresentation::calc(FractionCalc a)
{
    QString s;

    if (ui->radioButtonSumm->isChecked())
    {
        s=a.calculate(FractionCalc::summ);
    }
    else if(ui->radioButtonMulti->isChecked())
    {
       s=a.calculate(FractionCalc::multi);
    }
    else if(ui->radioButtonDivision->isChecked())
    {
        s=a.calculate(FractionCalc::div);
    }
    else s=a.calculate(FractionCalc::subt);

    wV->setHtml(s);
}

void WindowPresentation::on_pushButtonDemo_clicked()//кнопка демонстрация
{
   ui->lineEditError->setVisible(false);//сообщение об ошибке - установить видимым
   if (isDataOk())
   {
       int t1, n1, d1, t2, n2, d2, lp1, lp2, rp1, rp2;
       QString lETotal1, lENum1, lEDen1, lETotal2, lENum2, lEDen2, lEDec1, lEDec2;

       lETotal1=ui->lineEditTotal1->text();//считали значение из окна Total1
       t1=lETotal1.toInt();//перевели строку в число

       lETotal2=ui->lineEditTotal2->text();//считали значение из окна Total2
       t2=lETotal2.toInt();//Перевели строку в число

       lENum1=ui->lineEditNumerator1->text();//считали значение из окна Numerator1
       n1=lENum1.toInt();

       lENum2=ui->lineEditNumerator2->text();//считали значение из окна Numerator2
       n2=lENum2.toInt();//Перевели строку в число

       lEDen1=ui->lineEditDenominator1->text();//считали значение из окна Denominator1
       d1=lEDen1.toInt();

       lEDen2=ui->lineEditDenominator2->text();//считали значение из окна Denominator2
       d2=lEDen2.toInt();//Перевели строку в число

       Sign aSign=positiveSign, bSign=negativeSign;
       QString checkSign1 = ui->lineEditSign1->text();
       QString checkSign2 = ui->lineEditSign2->text();
       QString minusString = "-";
       int aa=0, bb=0;
       if(checkSign1.length()>0)
       {
           qDebug()<<"Зашёл";
           aSign=negativeSign;
           aa=-1;
       }
       else aSign==positiveSign;
       if(ui->lineEditSign2->text().length()>0)
       {
           bSign=negativeSign;
           bb=-1;
       }
       else bSign=positiveSign;

       lEDec1=ui->lineEditDecimal1->text();

       lEDec2=ui->lineEditDecimal2->text();

       if (ui->lineEditTotal1->isEnabled())
       {
         FractionCalc::RegFr rfa1(t1, n1, d1, aSign);

         if (ui->lineEditTotal2->isEnabled())
         {
           FractionCalc::RegFr rfa2(t2, n2, d2, bSign);
           FractionCalc a(rfa1, rfa2);
           calc(a);
         }
         else
         {
             QList <QString> listDec;
             lEDec2=lEDec2.replace(",",".");
             listDec=lEDec2.split(".");
             lp2= listDec[0].toInt();
             rp2=listDec[1].toInt();
             FractionCalc::DecFr df2(lp2,rp2, bSign);
             FractionCalc a(rfa1, df2);
             calc(a);
         }
       }
       else
       {
           QList <QString> listDec;
           lEDec1=lEDec1.replace(",",".");
           listDec=lEDec1.split(".");
           lp1= listDec[0].toInt();
           rp1=listDec[1].toInt();
           FractionCalc::DecFr df1(lp1,rp1, aSign);
           if (ui->lineEditTotal2->isEnabled())
           {
             FractionCalc::RegFr rfa2(t2, n2, d2, bSign);
             FractionCalc a(df1, rfa2);
             calc(a);
           }
           else
           {
               QList <QString> listDec2;
               lEDec2=lEDec2.replace(",",".");
               listDec2=lEDec2.split(".");
               lp2= listDec2[0].toInt();
               rp2=listDec2[1].toInt();
               FractionCalc::DecFr df2(lp2,rp2, bSign);
               FractionCalc a(df1, df2);
               calc(a);
           }
       }
    }
       else ui->lineEditError->setVisible(true);//показать сообщение об ошибке
}

 bool WindowPresentation::testRegExpNumberDoub17(QString fr)//функция для работы с регулярными выражениями
 {
     QRegularExpression reg("^[\\d]{1,7}[,.]?[\\d]{1,7}$");
     QRegularExpressionMatch match = reg.match(fr);//объект, кот хранит информацию о проверке на соответствие
     if (match.hasMatch())//соответствие найдено?
     {
         return true;
     }
     else return false;
 }

bool WindowPresentation::testRegExpNumber(QString fr)//функция для работы с регулярными выражениями (для чисел)
{
    QRegularExpression reg("^[\\d]{0,7}$");
    QRegularExpressionMatch match = reg.match(fr);//объект, кот хранит информацию о проверке на соответствие
    if (match.hasMatch())//соответствие найдено?
    {
        return true;
    }
    else return false;
}

bool WindowPresentation::testRegExpNumberDoub(QString fr)//функция для работы с регулярными выражениями (для чисел с плавающей точкой)
{
    QRegularExpression reg("^[\\d]{1,7}[,.]?[\\d]*$");
    QRegularExpressionMatch match = reg.match(fr);//объект, кот хранит информацию о проверке на соответствие
    if (match.hasMatch())//соответствие найдено?
    {
        return true;
    }
    else return false;
}

void WindowPresentation::on_lineEditTotal1_textChanged(const QString &arg1)//окно, отвечающее за целое число1
{
    checkHasText();//проверка есть ли текст
    bool dig = testRegExpNumber(arg1);//
    if (dig==true)
    {
        lETotal1=arg1;
    }
    else
    {
        ui->lineEditTotal1->setText(lETotal1);
    }
}

bool WindowPresentation::testRegExpMark(QString mr)//функция для работы с регулярными выражениями (для знака"-")
{
    QRegularExpression reg("^[-]?$");
    QRegularExpressionMatch match = reg.match(mr);//объект, кот хранит информацию о проверке на соответствие
    if (match.hasMatch())//соответствие найдено?
    {
        return true;
    }
    else return false;
}

void WindowPresentation::on_lineEditSign1_textChanged(const QString &arg1)//окно, отвечающее за знак1
{
    bool sig = testRegExpMark(arg1);
    if (sig==true)
    {
        lESign1=arg1;
    }
    else
    {
        ui->lineEditSign1->setText(lESign1);
    }
}


void WindowPresentation::on_lineEditSign2_textChanged(const QString &arg1)//окно, отвечающее за знак2
{
    bool sig = testRegExpMark(arg1);
    if (sig==true)
    {
        lESign2=arg1;
    }
    else
    {
        ui->lineEditSign2->setText(lESign2);
    }
}

void WindowPresentation::on_lineEditNumerator1_textChanged(const QString &arg1)//окно, отвечающее за числитель 1
{
    checkHasText();
    bool dig = testRegExpNumber(arg1);
    if (dig==true)
    {
        lENum1=arg1;
    }
    else
    {
        ui->lineEditNumerator1->setText(lENum1);
    }
}

void WindowPresentation::on_lineEditTotal2_textChanged(const QString &arg1)//окно, отвечающее за целую часть 2-ой дроби
{
    checkHasText2();
    bool dig = testRegExpNumber(arg1);
    if (dig==true)
    {
        lETotal2=arg1;
    }
    else
    {
        ui->lineEditTotal2->setText(lETotal2);
    }
}

void WindowPresentation::on_lineEditNumerator2_textChanged(const QString &arg1)//окно, отвечающее за числитель 2-ой дроби
{
    checkHasText2();
    bool dig = testRegExpNumber(arg1);
    if (dig==true)
    {
        lENum2=arg1;
    }
    else
    {
        ui->lineEditNumerator2->setText(lENum2);
    }
}

void WindowPresentation::on_lineEditDenominator1_textChanged(const QString &arg1)//окно, отвечающее за знаменатель 1-ой дроби
{
    checkHasText();
    bool dig = testRegExpNumber(arg1);
    if (dig==true)
    {
        lEDen1=arg1;
    }
    else
    {
        ui->lineEditDenominator1->setText(lEDen1);
    }
}

void WindowPresentation::on_lineEditDenominator2_textChanged(const QString &arg1)//окно, отвечающее за знаменатель 2-ой дроби
{
    checkHasText2();
    bool dig = testRegExpNumber(arg1);
    if (dig==true)
    {
        lEDen2=arg1;
    }
    else
    {
        ui->lineEditDenominator2->setText(lEDen2);
    }
}

void WindowPresentation::on_lineEditDecimal1_textChanged(const QString &arg1)//окно, отвечающее за десятичную дробь 1ую
{
    if(ui->lineEditDecimal1->text().length()>0)
    {
        ui->lineEditTotal1->setEnabled(false);
        ui->lineEditDenominator1->setEnabled(false);
        ui->lineEditNumerator1->setEnabled(false);
    }
    else
    {
        ui->lineEditTotal1->setEnabled(true);
        ui->lineEditDenominator1->setEnabled(true);
        ui->lineEditNumerator1->setEnabled(true);
    }
    bool dig = testRegExpNumberDoub(arg1);
    bool dig2= testRegExpNumber(arg1);
    if ((dig==true)||(dig2==true))
    {
        lEDec1=arg1;
    }
    else
    {
        ui->lineEditDecimal1->setText(lEDec1);
    }
}


void WindowPresentation::on_lineEditDecimal2_textChanged(const QString &arg1)//окно, отвечающее за десятичную дробь 2ую
{
    if(ui->lineEditDecimal2->text().length()>0)
    {
        ui->lineEditTotal2->setEnabled(false);
        ui->lineEditDenominator2->setEnabled(false);
        ui->lineEditNumerator2->setEnabled(false);
    }
    else
    {
        ui->lineEditTotal2->setEnabled(true);
        ui->lineEditDenominator2->setEnabled(true);
        ui->lineEditNumerator2->setEnabled(true);
    }
    bool dig=testRegExpNumberDoub(arg1);
    bool dig2= testRegExpNumber(arg1);
    if ((dig==true)||(dig2==true))
    {
        lEDec2=arg1;
    }
    else
    {
        ui->lineEditDecimal2->setText(lEDec2);
    }
}
void WindowPresentation::checkHasText()//проверка есть ли текст
{   //если в Total1 есть текст или в числителе есть текст или в знаменателе есть текст
    if ((ui->lineEditTotal1->text().length()>0)||(ui->lineEditDenominator1->text().length()>0)||(ui->lineEditNumerator1->text().length()>0))
    {
        ui->lineEditDecimal1->setEnabled(false);//блокируем окно с десятичной дробью
    }
    //если нет текста в окне целое, и нет текста в окне числитель, и нет текста в окне знаменатель
    if (!(ui->lineEditTotal1->text().length()>0)&&!(ui->lineEditDenominator1->text().length()>0)&&!(ui->lineEditNumerator1->text().length()>0))
    {
        ui->lineEditDecimal1->setEnabled(true);//не блокируем окно для десятичных дробей
    }
}

void WindowPresentation::checkHasText2()//проверка есть ли текст
{
    if ((ui->lineEditTotal2->text().length()>0)||(ui->lineEditDenominator2->text().length()>0)||(ui->lineEditNumerator2->text().length()>0))
    {
        ui->lineEditDecimal2->setEnabled(false);
    }
    if (!(ui->lineEditTotal2->text().length()>0)&&!(ui->lineEditDenominator2->text().length()>0)&&!(ui->lineEditNumerator2->text().length()>0))
    {
        ui->lineEditDecimal2->setEnabled(true);
    }
}

bool WindowPresentation::isDataOk()
{
   if (ui->lineEditTotal1->isEnabled())//если окно Total1 задействовано
   {
        if ((ui->lineEditTotal1->text()=="0")||(ui->lineEditDenominator1->text()=="0")||(ui->lineEditNumerator1->text()=="0"))//если в числителе текста нет или в знаменателе
       {
           return false;//показать сообщение об ошибке
       }

        if (((ui->lineEditDenominator1->text().length()>0)//если в окне знаменатель текст есть
             &&(!(ui->lineEditNumerator1->text().length()>0))) // и в окне числитель текста нет
                ||((!(ui->lineEditDenominator1->text().length()>0))&&(ui->lineEditNumerator1->text().length()>0)))//или в окне знаменатель текста нет и в окне числитель текст есть
        {
                return false;//показываем сообщение об ошибке
        }
        if ((((ui->lineEditDenominator1->text().length())>0 &&(ui->lineEditDenominator1->text()!="0"))//если в окне знаменатель текст есть
             &&(((ui->lineEditNumerator1->text().length()>0)&&(ui->lineEditNumerator1->text()=="0"))||((ui->lineEditNumerator1->text().length()<1)))) // и в окне числитель текста нет
                ||(((ui->lineEditNumerator1->text().length())>0 &&(ui->lineEditNumerator1->text()!="0"))//если в окне знаменатель текст есть
                   &&(((ui->lineEditDenominator1->text().length()>0)&&(ui->lineEditDenominator1->text()=="0"))||(ui->lineEditDenominator1->text().length()<1))) )//или в окне знаменатель текста нет и в окне числитель текст есть
        {
                return false;//показываем сообщение об ошибке
        }
        if(!((ui->lineEditTotal1->text().length())>0)&&(!(ui->lineEditDenominator1->text().length()>0))&&(!(ui->lineEditNumerator1->text().length()>0))&&(!(ui->lineEditDecimal1->text().length()>0)))
        {
                return false;//показываем сообщение об ошибке
        }
   }
   else //иначе
   {
        if(!testRegExpNumberDoub17(ui->lineEditDecimal1->text()))//если введенное значение не соотв. проверке
        {
            return false;//показываем сообщение об ошибке
        }
   }
    if(ui->lineEditTotal2->isEnabled())//если окно Total2 задействовано
    {
        if((ui->lineEditTotal2->text()=="0")||(ui->lineEditDenominator2->text()=="0")||(ui->lineEditNumerator2->text()=="0"))//если в числителе текста нет
        {
            return false;//показать окно об ошибке
        }

        if (((ui->lineEditDenominator2->text().length()>0)//если в знаменателе текст есть
             &&(!(ui->lineEditNumerator2->text().length()>0)))//и нет текста в числителе
                ||((!(ui->lineEditDenominator2->text().length()>0))&&(ui->lineEditNumerator2->text().length()>0)))//или нет текста в числителе и есть текст в знаменателе
        {
                return false;//показать сообщение об ошибке
        }
        if ((((ui->lineEditDenominator2->text().length())>0 &&(ui->lineEditDenominator2->text()!="0"))//если в окне знаменатель текст есть
             &&(((ui->lineEditNumerator2->text().length()>0)&&(ui->lineEditNumerator2->text()=="0"))||((ui->lineEditNumerator2->text().length()<1)))) // и в окне числитель текста нет
                ||(((ui->lineEditNumerator2->text().length())>0 &&(ui->lineEditNumerator2->text()!="0"))//если в окне знаменатель текст есть
                   &&(((ui->lineEditDenominator2->text().length()>0)&&(ui->lineEditDenominator2->text()=="0"))||(ui->lineEditDenominator2->text().length()<1))) )//или в окне знаменатель текста нет и в окне числитель текст есть
        {
                return false;//показываем сообщение об ошибке
        }
        if(!((ui->lineEditTotal2->text().length())>0)&&(!(ui->lineEditDenominator2->text().length()>0))&&(!(ui->lineEditNumerator2->text().length()>0))&&(!(ui->lineEditDecimal2->text().length()>0)))
        {
            return false;//показываем сообщение об ошибке
        }
    }
    else//иначе
    {
        if(!testRegExpNumberDoub17(ui->lineEditDecimal2->text()))//проверяем вводимые данные на корректность, если не корректны
        {
            return false;//показываем сообщение об ошибке
        }
    }
    return true;
}
