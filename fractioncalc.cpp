#include "fractioncalc.h"
#include <stdexcept>
#include <QDebug>
#include <QList>
#include <qmath.h>


FractionCalc::FractionCalc(RegFr a, RegFr b)//функция если у нас две смешанных(обыкновенных) дроби
{
    r1=a;
    r2=b;
    flag=1;
}

FractionCalc::FractionCalc(DecFr a, DecFr b)//функция если две десятичные дроби
{
    d1=a;
    d2=b;
    flag = 2;
}

FractionCalc::FractionCalc(RegFr a, DecFr b)//функция если первая дробь смешанная(обыкновенная), вторая - десятичная
{
    r1=a;
    d2=b;
    flag = 3;
}

FractionCalc::FractionCalc(DecFr a, RegFr b)//функция если первая дробь десятичная, вторая - смешанная(обыкновенная)
{
    d1=a;
    r2=b;
    flag = 4;
}

FractionCalc::RegFr::RegFr(int t, int n, int d,int s)//смешанная дробь: t-целая часть, n-числитель, d-знаменатель
{
    total=t;
    denom=d;
    numen=n;
    sign=s;

    if (d==0)//если знаменатель равен нулю
    {
        throw std::invalid_argument("denom is NULL");//исключение
    }
}

FractionCalc::RegFr::RegFr()
{
}
FractionCalc::DecFr::DecFr()
{
}
FractionCalc::RegFr::RegFr(FractionCalc::RegFr &a)
{
    total = a.total;
    denom = a.denom;
    numen = a.numen;
    sign = a.sign;
}
FractionCalc::DecFr::DecFr(int lp, int rp, int s)//десятичная дробь: rp - часть после ,; lp - часть до ,
{
    rigtPart = rp;
    leftPart=lp;
    sign=s;
}

QString FractionCalc::calculate (FrOperation frOper)//вычисляем здесь, в зависимости от комбинации дробей вариант 1, 2, 3 или 4
{
    QString sResult;
    switch (flag)
    {
        case 1://rr
        {
        if(frOper==div || frOper==multi)
        {
            r1=correctRegFr(r1);
            r1=reduceFraction(r1);
            r2=reduceFraction(r2);
            r2=correctRegFr(r2);
        }
            preOperation(frOper);
        }
        break;

        case 2://dd
        {
            preOperation(frOper);
        }
        break;

        case 3://rd
        {
        if(frOper==div||frOper==multi)
        {
             r1=reduceFraction(r1);
        }
        else
        {
            r1=correctRegFr(r1);
            r1=reduceFraction(r1);
        }
            preOperation(frOper);
        }
        break;

        case 4://dr
        {
        if (frOper==div||frOper==multi)
        {
            r2=reduceFraction(r2);
        }
        else
        {
            r2=correctRegFr(r2);
            r2=reduceFraction(r2);
        }
            preOperation(frOper);

        }
        break;

        default:
        {
            sResult = "Неопределенная ошибка";
        }
    }
    sResult=getTextList();
    return sResult;
}

QString FractionCalc::getFractionString (RegFr a)//выводит дробь в красивом правильном формате
{

    if(a.denom<0)
        a.denom*=-1;
    if (a.numen<0)
        a.numen*=-1;
    if (a.total<0)
        a.total*=-1;

    QString s="<table>"
            "<tr>";
    if(!(a.total==0))
    {
        QString sSign="";
        if(a.sign==negativeSign)
        {
            sSign = "-";
        }
           s+= "<td rowspan=2>"+sSign+
            QString::number(a.total)+
            "</td>";
    }
    else
    {
        QString sSign="";
        if(a.sign==negativeSign)
        {
            sSign = "-";
        }
           s+= "<td rowspan=2>"+sSign+
            "</td>";
    }
    if((!(a.denom==0))&&(!(a.numen==0)))
    {
         s+="<td></td><td style=\"border-bottom:solid black 1px;\">"+
          QString::number(a.numen)+
            "</td>"
          "</tr>"
          "<tr>"
            "<td></td>"
            "<td>"+
          QString::number(a.denom)+
            "</td>";
    }
       s+="</tr>"
            "</table>";
    return s;
}

FractionCalc::RegFr FractionCalc::reduceFraction (RegFr a)//сокращение дроби
{
    QString s;
    s="<!Doctype html><html><head><head><body>";
    s+= ("<h3>Сокращение дроби</h3>");
    s+="</body></html>";

    RegFr b(a.total,a.numen, a.denom, a.sign);
    s+=("Сократим дробь: ")+getFractionString(b);
    int j=-1;
    for(int i=b.numen; i>=2; i--)
    {
        if((b.numen%i==0)&&(b.denom%i==0))
        {
            j=i;
            break;
        }
    }
    if (!(j==-1))//если j = -1, то дробь не сокращаем
    {
        b.numen=b.numen/j;
        b.denom=b.denom/j;
        s+=("Находим число, на которое можно сократить числитель и знаменатель: "+QString::number(j)+ ".\n");
        s+=("Делим числитель и знаменатель на это число.\n");
        s+= ("Результать сокращения: ")+getFractionString(b)+"\n";
        stepsList.append(s);
    }
    return b;
}

QString FractionCalc::getTextList()//метод который выдает полностью текст
{
    QString s;
    if (!(stepsList.isEmpty()))
    {
        s="<!Doctype html><html><head><head><body>";
        for (int i=0; i<stepsList.length(); ++i)
        {
            s=s+("<h2> Шаг: "+QString::number(i+1)+"</h2>");
            s+= stepsList[i];
            s+="\n";
        }
        s+="</body></html>";
    }
    else s="Данные для отображения отсутствуют!";
    return s;
}

void FractionCalc::preOperation(FrOperation nameOperation)//приводим дробь к общему виду
{
     QString s;

    if(flag==1)//rr
    {

    }

    else if((flag ==2)&&((nameOperation==multi)||(nameOperation==div)))//dd
    {
        if(d1.rigtPart>0)
        {
            RegFr a(d1.leftPart,d1.rigtPart,makeDecDenominator(d1.rigtPart), d1.sign);
            r1 = a;
            s+=("Число до запятой надо записать как целую часть искомого смешанного числа "+QString::number(d1.leftPart)+".");
            s+=("В числитель дробной части нужно записать число, "
                "полученное из части после запятой "+QString::number(d1.rigtPart)+".");
            s+=("В знаменателе дробной части нужно записать цифру 1, к которой справа дописать столько нулей,"
                " сколько цифр находится в записи исходной десятичной дроби после запятой ");
        }
        //когда целая часть у десятичной дроби равна нулю ex. 0,5, 1- это числитель
        else {
            RegFr a(0,d1.rigtPart,1, d1.sign);
            r1=a;
        }

        if(d2.rigtPart>0)
        {
            RegFr a(d2.leftPart,d2.rigtPart,makeDecDenominator(d2.rigtPart), d2.sign);
            r2 = a;
        }
        //когда целая часть у десятичной дроби равна нулю ex. 0,5, 1- это числитель
        else {
            RegFr a(0,d2.rigtPart,1, d2.sign);
            r2=a;
        }
    }
    if(flag==3)//rd
    {
        s="<!Doctype html><html><head><head><body>";
        s+= ("<h3>Перевод десятичной дроби в обыкновенную</h3>");
        s+="</body></html>";

        if(d2.rigtPart>0)
        {
            RegFr a(d2.leftPart,d2.rigtPart,makeDecDenominator(d2.rigtPart), d2.sign);
            r2 = a;
        }
        //когда целая часть у десятичной дроби равна нулю ex. 0,5, 1- это числитель
        else {
            RegFr a(0,d2.rigtPart,1, d2.sign);
            r2=a;
        }
        s+="Приводим десятичную дробь к общему виду: "+getFractionString(r2) + "\n";

        stepsList.append(s);
    }
    else if (flag==4) //dr
    {
        s="<!Doctype html><html><head><head><body>";
        s+= ("<h3>Перевод десятичной дроби в обыкновенную</h3>");
        s+="</body></html>";

        if(d1.rigtPart>0)
        {
            RegFr a(d1.leftPart,d1.rigtPart,makeDecDenominator(d1.rigtPart), d1.sign);
            r1=a;
        }
        else {
            RegFr a(0,d1.rigtPart,1, d1.sign);
            r1=a;
             }
        s+="Приводим десятичную дробь к общему виду: "+getFractionString(r1) + "\n";

        stepsList.append(s);
    }

    switch (nameOperation)
    {
        case summ:
        {
            if(flag==2)
            {
                summDec();
            }
            else
                signSumm();
        }
            break;

        case div:
        if(flag==2)
        {
            divisionDec();
        }
        else
        signDivision();
            break;

        case subt:
        {
            if(flag==2)
            {
                subtractionDec();
            }
            else
             signSubstraction();
        }
            break;

        case multi:
        if(flag==2)
        {
            multiplicationDec();
        }
        else
        signMultiplication();
            break;

        default:
            break;
    }
}

int FractionCalc::makeDecDenominator (int nm)//формирование знаменателя
{
    QString s;
    s=QString::number(nm);//nm - это десятичная часть
    int d=1;
    for (int i=0; i<s.length(); i++)
    {
        d*=10;
    }
    return d;
}

QString FractionCalc::getOneDen ()//общий знаменатель
{
    QString s;
    s="<!Doctype html><html><head><head><body>";
    s+= ("<h3>Нахождение общего знаменателя</h3>");
    s+="</body></html>";
    QList <int> a= getDenomsSet(r1.denom);
    QList <int> b= getDenomsSet(r2.denom);
    QList <int> r=a;

    for(int i=0; i<r.length(); i++)
    {
        while(a.contains(r[i])&&b.contains(r[i]))//пока зн1 и зн2 содержит
        {
             a.removeOne(r[i]);//удаляем из зн1
             b.removeOne(r[i]);//удаляем из зн2

         }
    }
             int x=1, y=1;
             for(int i=0; i<a.length();i++)
             {
                 x*=a[i];
             }

             for(int i=0; i<b.length(); i++)
             {
                 y*=b[i];
             }

             s+=("Находим дополнительные множители: " + QString::number(x) + " и " + QString::number(y)+".\n");

             r1.numen*=y;
             r2.numen*=x;
             r1.denom*=y;
             r2.denom*=x;
             s+=("Числитель и знаменатель каждой дроби умножаем на свой дополнительный "
                 "множитель. Числитель первой дроби: "+QString::number(r1.numen)+", "
                 +"числитель второй дроби: "+QString::number(r2.numen)+", "
                 +"знаменатель первой дроби: "+QString::number(r1.denom)+", "
                 +"знаменатель второй дроби: "+QString::number(r2.denom)+".\n");
             stepsList.append(s);

    return "";
 }

QList <int> FractionCalc::getDenomsSet(int x)//x- знаменатель simpleDens - это простые множители знаменателя
{
    QList <int> s;
    int a=x;
    while (a>1)
    {
        for(int i=2; i<=a; i++)
        {
            if (a%i==0)
            {
                s.append(i);
                a/=i;
                break;
            }
        }
    }
   return s;
}

FractionCalc::RegFr FractionCalc::operationSumm ()//сложение двух простых дробей
{
    QString s;
    RegFr th;
    s="<!Doctype html><html><head><head><body>";
    s+= ("<h3>Сложение двух простых дробей</h3>");
    s+="</body></html>";
    th.total=r1.total+r2.total;
    s+=("Складываем целые части дробей: " + QString::number(r1.total)
        + " и " +QString::number(r2.total) + " = "+QString::number(th.total)+".\n");
    th.numen=r1.numen+r2.numen;
    s+=("Складываем числители: "+QString::number(r1.numen)+ " + " + QString::number(r2.numen)
        + " = " +QString::number(th.numen)+".\n");
    th.denom=r1.denom;
    s+=("Знаменатель равен: " + QString::number(th.denom)+".\n");
    s+=("Результат: " + getFractionString(th));
    stepsList.append(s);
    th=correctRegFr(th);
    th=reduceFraction(th);
    return th;

}
int FractionCalc::compareBigger(FractionCalc::RegFr a, FractionCalc::RegFr b)//без знаменателя
{
    if(a.total>b.total)
    {
        return 1;
    }
    else if(a.total<b.total)
    {
        return -1;
    }
    else
    {
        if(a.numen>b.numen)
        {
            return 1;
        }
        else if(a.numen<b.numen)
        {
            return -1;
        }
        else return 0;
    }
    return 0;
}
FractionCalc::RegFr FractionCalc::signSubstraction()
{
    QString s;
    s+= getOneDen();
    Sign resSign = positiveSign;
    if(r2.sign==negativeSign)//меняем знак на положительный и вызываем сложение
    {
        RegFr r;
        r2.sign=1;
        r = signSumm();
        return r;
    }
    else
    {
        if(r1.sign==negativeSign)
        {
            resSign = negativeSign;
            RegFr r;
            r = operationSumm();
            r.sign = resSign;
            return r;
        }
        else if(compareBigger(r1,r2)==-1)
        {
            resSign = negativeSign;
            RegFr r;
            r  = operationSubtraction();
            r.sign = resSign;
            return r;
        }
    }
    RegFr r(0,0,0,positiveSign);
    return r;
}
FractionCalc::RegFr FractionCalc::signSumm ()
{
    QString s;
    s+= getOneDen();
    Sign sg = positiveSign;

    if(r2.sign==negativeSign)
    {
            if(compareBigger(r2,r1)==1)
            {
                sg = negativeSign;
            }
            RegFr r;
            r =  operationSubtraction();
            r.sign = sg;
            return r;
    }
    else if(r1.sign==negativeSign)
    {
        if(r2.sign==negativeSign)
        {
            sg=negativeSign;
            RegFr r;
            r =  operationSumm();
            r.sign = sg;
            return r;
        }
        else
        {
            if(compareBigger(r1,r2)==1)
            {
                sg = negativeSign;
            }
            RegFr r;
            r =  operationSubtraction();
            r.sign = sg;
            return r;
        }
    }
    else
    {
        sg=1;
        RegFr r;
        r =  operationSumm();
        r.sign = sg;
        return r;
    }
    stepsList.append(s);
    RegFr r(0,0,0,1);
    return r;
}
FractionCalc::RegFr FractionCalc::signMultiplication()
{
    Sign sg = positiveSign;
    if(r1.sign==negativeSign && r2.sign==positiveSign)
    {
        sg = negativeSign;
    }
    else if (r2.sign==negativeSign && r1.sign==positiveSign)
    {
        sg = negativeSign;
    }
    RegFr r;
    r = operationMultiplication();
    r.sign = sg;
    return r;
}
FractionCalc::RegFr FractionCalc::signDivision()
{
    Sign sg = positiveSign;
    if(r1.sign==negativeSign && r2.sign==positiveSign)
    {
        sg = negativeSign;
    }
    else if (r2.sign==negativeSign && r1.sign==positiveSign)
    {
        sg = negativeSign;
    }
    RegFr r;
    r = operationDivision();
    r.sign = sg;
    return r;
}

FractionCalc::RegFr FractionCalc::operationSubtraction()//вычитание двух простых дробей
{
    QString s;
    RegFr th;
    s="<!Doctype html><html><head><head><body>";
    s+= ("<h3>Вычитание двух простых дробей</h3>");
    s+="</body></html>";
    if((r1.numen==r2.numen)&&(r1.total==r2.total)&&(r1.denom==r2.denom))
    {
        s+=("Дробь " + getFractionString(r1) + " и дробь" + getFractionString(r2) + " равны. Результат: 0.\n");
    }
    else
    {
        th.total=r1.total-r2.total;
        s+=("Вычитаем целые части дробей: " + QString::number(r1.total)
            + " и " +QString::number(r2.total) + " = "+QString::number(th.total)+".\n");

        if(r1.numen<r2.numen)
        {
            int aaa = r1.denom + r1.numen;
            th.numen = aaa-r2.numen;
            th.total--;
        }
        else
        {
            th.numen=r1.numen-r2.numen;
            s+=("Вычитаем числители: "+QString::number(r1.numen)+ " - " + QString::number(r2.numen)
                + " = " +QString::number(th.numen)+".\n");
        }

        th.denom=r1.denom;
        s+=("Знаменатель равен: " + QString::number(th.denom)+".\n");
        th=reduceFraction(th);
        th=correctRegFr(th);
        s+=("Результат: " + getFractionString(th)+"\n");
    }

    stepsList.append(s);
    return th;
}

FractionCalc::RegFr FractionCalc::operationMultiplication()//операция умножения обычных дробей
{
    r1=conversFrWrong(r1);
    r2=conversFrWrong(r2);
    QString s;
    s="<!Doctype html><html><head><head><body>";
    s+= ("<h3>Умножение двух простых дробей</h3>");
    s+="</body></html>";
    RegFr th;
    th.total=0;
    th.numen=r1.numen*r2.numen;
    s+=("Умножаем числитель первой дроби " + QString::number(r1.numen)
        + " на числитель второй дроби " + QString::number(r2.numen) + ".\n");

    th.denom=r1.denom*r2.denom;
    s+=("Умножаем знаменатель первой дроби " + QString::number(r1.denom)
        + " на знаменатель второй дроби " + QString::number(r2.denom) + ".\n");
    s+=("Результат: " + getFractionString(th));
    stepsList.append(s);
    th=reduceFraction(th);
    th=correctRegFr(th);

    return th;
}

FractionCalc::RegFr FractionCalc::operationDivision()//операция деления обычных дробей
{
    r1=conversFrWrong(r1);
    r2=conversFrWrong(r2);
    QString s;
    s="<!Doctype html><html><head><head><body>";
    s+= ("<h3>Деление двух простых дробей</h3>");
    s+="</body></html>";
    RegFr th;
    th.total=0;

    th.numen=r1.numen*r2.denom;
    s+=("Умножаем числитель первой дроби " + QString::number(r1.numen)
        + " на знаменатель второй дроби " + QString::number(r2.denom) + ".\n");

    th.denom=r1.denom*r2.numen;

    s+=("Умножаем знаменатель первой дроби " + QString::number(r1.denom)
        + " на числитель второй дроби " + QString::number(r2.numen) + ".\n");
    th=reduceFraction(th);
    th=correctRegFr(th);
    s+=("Результат: " + getFractionString(th));
    stepsList.append(s);
    return th;
}

FractionCalc::RegFr FractionCalc::conversFrWrong(RegFr r)//проверяем дробь, есть ли целая часть и переводим ее, чтобы умножать и делить
{
    if (r.total>0)
    {
        QString s;
        s+="<!Doctype html><html><head><head><body>";
        s+=("<h3>Перевод смешанного числа в неправильную дробь</h3>");
        s+="</body></html>";
        s+=("Целую часть " + QString::number(r.total)+
            " умножим на знаменатель " + QString::number(r.denom) +
            " и к произведению прибавим числитель " + QString::number(r.numen) +"." + "\n");

        r.numen=(r.denom*r.total)+r.numen;
        r.total=0;
        s+= ("Результат запишем в числитель " + QString::number(r.numen) +"." + "\n");
        s+= ("Знаменатель оставляем без изменения " + QString::number(r.denom) + "." + "\n");
        s+= ("Результат преобразования: " + getFractionString(r));
        stepsList.append(s);
    }
    return r;
}

FractionCalc::DecFr FractionCalc::summDec()//сложение десятичных дробей
{
    double a, b,c;
    QString s;
    s="<!Doctype html><html><head><head><body>";
    s+= ("<h3>Сложение десятичных дробей</h3>");
    s+="</body></html>";
    a=fromDecFrToDouble(d1);
    b=fromDecFrToDouble(d2);
    c=a+b;
    s=("Чтобы сложить " + QString::number(fromDecFrToDouble(d1)) + " и " + QString::number(fromDecFrToDouble(d2)) +" записываем их запятая под запятой.\n");
    s+=("Затем складываем цифры по разрядам и в полученном ответе сносим запятую под запятой.\n");
    s+=getDecimalString(c, summ);
    DecFr d=fromDoubleToDecFr(c);
    stepsList.append(s);
    return d;
}

FractionCalc::DecFr FractionCalc::subtractionDec()//вычитание десятичных дробей
{
    double a, b,c;
    QString s;
    s="<!Doctype html><html><head><head><body>";
    s+= ("<h3>Вычитание десятичных дробей</h3>");
    s+="</body></html>";
    a=fromDecFrToDouble(d1);
    b=fromDecFrToDouble(d2);
    if (a==b)
    {
        s+=("Дробь " + QString::number(a) +
            " и дробь " + QString::number(b) + " равны. Результат: 0.\n");
    }
    else
    {
    c=a-b;
    s=("При вычитании десятичных дробей их следует записать так, "
       "чтобы запятые находились строго одна под другой.\n");
    s+=("Вычитаем числа, не обращая внимания на запятую.\n");
    s+=("Сносим запятую под запятыми.\n");
    s+=getDecimalString(c, subt);
    }
    DecFr d=fromDoubleToDecFr(c);
    stepsList.append(s);
    return d;
}

FractionCalc::DecFr FractionCalc::multiplicationDec()//умножение десятичных дробей
{
    double a, b, c;
    QString s;
    s="<!Doctype html><html><head><head><body>";
    s+= ("<h3>Умножеине десятичных дробей</h3>");
    s+="</body></html>";
    a=fromDecFrToDouble(d1);
    b=fromDecFrToDouble(d2);
    c=a*b;
    s=("Десятичные дроби запишем в столбик и умножим как обыкновенные числа.\n");
    s+=("В полученном произведении отделим после запятой столько цифр,"
        " сколько их после запятых в обоих множителях вместе.");
    s+=getDecimalString(c,multi);
    DecFr d=fromDoubleToDecFr(c);
    stepsList.append(s);
    return d;
}

FractionCalc::DecFr FractionCalc::divisionDec()//деление десятичных дробей
{
    double a, b, c;
    QString s;
    s="<!Doctype html><html><head><head><body>";
    s+= ("<h3>Деление десятичных дробей</h3>");
    s+="</body></html>";
    a=fromDecFrToDouble(d1);
    b=fromDecFrToDouble(d2);
    c=a/b;
    s=("Разделим " + QString::number(fromDecFrToDouble(d1))+" на " +QString::number(fromDecFrToDouble(d2))+".\n");
    s+=("В делимом и в делителе запятую перенести на столько цифр вправо,"
        " сколько их в делителе после запятой. После этого выполнить деление натуральных чисел.\n");
    s+=("Когда закончится деление целой части, в частном поставить запятую.\n");
    s+=getDecimalDivString(c);
    DecFr d=fromDoubleToDecFr(c);
    stepsList.append(s);
    return d;
}

double FractionCalc::fromDecFrToDouble(DecFr a)//из десятичной дроби в тип число с плавающей точкой
{
    double x, y;
    x=a.leftPart;
    y=a.rigtPart;

    while(y>1)
    {
        y/=10;
    }
    x+=y;
    x*=a.sign;
    return x;
}

FractionCalc::DecFr FractionCalc::fromDoubleToDecFr (double x)//из числа с плавающей точкой в десятичную дробь
{
    int a, b;
    Sign sg;
    QString s=QString::number(x);
    QList <QString> listDec;
    s=s.replace(",",".");
    listDec=s.split(".");
    a= listDec[0].toInt();
    b=listDec[1].toInt();
    if(x>=0)
    {
        sg=positiveSign;
    }
    else sg=negativeSign;

    DecFr d(a,b,sg);
    return d;
}

QString FractionCalc::getDecimalString(double d, FrOperation f)//функция выводит красиво вычисления в столбик
{
    QString s;
    s="<table>"
"<tr>"
   "<td rowspan=2>" + getOperationString(f) + "</td>"
   "<td>" + QString::number(fromDecFrToDouble(d1)) + "</td>"
"</tr>"
"<tr>"
   "<td style=\"border-bottom:solid black 1px;\">" + QString::number(fromDecFrToDouble(d2)) + "</td>"
"</tr>"
"<tr>"
   "<td>""</td>"
   "<td>"+QString::number(d)+"</td>"
"</tr>"
"</table>";
    return s;
}

QString FractionCalc::getDecimalDivString(double d)//функция выводит красиво вычисления в столбик для деления
{
    QString s;
    s="<table>""<tbody>"
    "<tr>"
    "<td rowspan=2>""</td>"
    "<td colspan=2>"+QString::number(fromDecFrToDouble(d1))+"</td>"
    "<td colspan=2 style=\"BORDER-left: 1px solid #000000;\">"+QString::number(fromDecFrToDouble(d2))+"</td>"
    "</tr>"
    "<tr>"
   "<td colspan=2>""</td>"
    "<td colspan=7 style=\"BORDER-left: 1px solid #000000;BORDER-top: 1px solid #000000;\">"+QString::number(d)+"</td>"
    "</tr>"
    "</table>";
    return s;
}

QString FractionCalc::getOperationString (FrOperation f)//функция которая вставляет знак операции при вычислении столбиком
{
    switch (f) {
    case summ:
    {
        return "+";
    }

        break;
    case multi:
    {
        return "*";
    }

        break;

    case div:
    {
        return ":";
    }

        break;
    case subt:
    {
        return "-";
    }

        break;

    default:
    {
        return "+";
    }
        break;
    }
}
FractionCalc::RegFr FractionCalc::correctRegFr (RegFr r)//приводим дробь к правильной записи
{
  int n, d, t;//t целая часть, n знаменатель, d числитель
  d=r.denom;
  n=r.numen;
  t=r.total;

  if (n>d)
  {
      QString s;
      s="<!Doctype html><html><head><head><body>";
      s+= ("<h3>Перевод неправильной дроби в смешанное число</h3>");
      s+="</body></html>";
      s+= ("Числитель больше знаменателя: " + QString::number(n)+">"+QString::number(d)+"."+"\n");
      t=(n/d)+t;
      s+=("Делим числитель на знаменатель и получаем: " + QString::number(n/d)+"."+"\n");
      s+=("Прибавляем полученное целое число к целой части: " + QString::number(t)+"."+"\n");
      n=n%d;
      s+=("В числитель записываем остаток от деления числителя на знаменатель, "
         "а знаменатель оставляем тем же: "+
         QString::number(n)+"/"+QString::number(d)+"."+"\n");
      s+= ("Результат преобразования: ");
      RegFr k(t, n, d, r.sign);

      s+= getFractionString(k);
      stepsList.append(s);
  }

    if(n==d)
    {
        QString s;
        s="<!Doctype html><html><head><head><body>";
        s+= ("<h3>Упрощение дроби</h3>");
        s+="</body></html>";
        s+=("Если числитель равен знаменателю, то дробь равна 1.");
        t++;
        s+=("Прибавляем единицу к целой части : "+ QString::number(t)+"."+"\n");
        s+= ("Результат преобразования: ");
        stepsList.append(s);
    }

    else if(n==0)
    {
        QString s=("Дробь равна нулю, если числитель равен нулю, а знаменатель отличен от нуля.\n");
        s+=("Записываем только целую часть: " + QString::number(t)+"."+"\n");
        d=0;
        s+= ("Результат преобразования: ");
        stepsList.append(s);
    }
    r.total=t;
    r.denom=d;
    r.numen=n;
    return r;
}
