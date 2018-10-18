#ifndef FRACTIONCALC_H
#define FRACTIONCALC_H
#include <QWidget>
typedef int Sign;
static const Sign positiveSign = 1;
static const Sign negativeSign = -1;

class FractionCalc
{
public:
    enum FrOperation
    {
        subt=0, summ=1, div=2, multi=3
    };
    struct RegFr //Для дроби
    {
        int total;
        int denom;
        int numen;
        int sign;
        RegFr(int t, int n, int d, int sign);//в RegFr храним целую часть, числитель и знаменатель
        RegFr();//по умолчанию
        RegFr(RegFr &a);
    };

    struct DecFr//для десятичной
    {
        int leftPart;//левая часть до ,
        int rigtPart;//правая часть после ,
        Sign sign;

        DecFr(int lp, int rp, int sign);//левая часть и правая часть (0,0)
        DecFr();
        //DecFr(DecFr &a);
    };

    FractionCalc(RegFr a, RegFr b);//1
    FractionCalc(DecFr a, DecFr b);//2
    FractionCalc(RegFr a, DecFr b);//3
    FractionCalc(DecFr a, RegFr b);//4
    QString calculate (FrOperation);

private:
    RegFr r1;
    RegFr r2;
    DecFr d1;
    DecFr d2;
    int flag;
    QList <QString> stepsList;//список шагов - объяснение для пользователя
    RegFr correctRegFr (RegFr r);
    QString getFractionString(RegFr a);
    RegFr reduceFraction (RegFr);
    QString getTextList();
    void preOperation(FrOperation);
    double fromDecFrToDouble(DecFr a);
    DecFr fromDoubleToDecFr (double x);
    int makeDecDenominator (int );
    RegFr operationSubtraction ();
    RegFr operationSumm ();
    RegFr operationMultiplication();
    RegFr operationDivision();
    RegFr conversFrWrong(RegFr r);
    DecFr summDec();
    DecFr subtractionDec();
    QList <int> getDenomsSet(int x);
    DecFr multiplicationDec();
    DecFr divisionDec();
    QString getOneDen();
    QString getDecimalString(double d, FrOperation f);
    QString getOperationString (FrOperation);
    QString getDecimalDivString(double d);
    RegFr signSubstraction();
    RegFr signSumm ();
    RegFr signMultiplication();
    RegFr signDivision();
    int compareBigger(RegFr a, RegFr b);
};

#endif // FRACTIONCALC_H
