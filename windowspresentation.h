#ifndef WINDOWPRESENTATION_H
#define WINDOWPRESENTATION_H

#include <QWidget>
#include <QWebView>
#include "fractioncalc.h"
#include <QList>

namespace Ui {
class WindowPresentation;
}

class WindowPresentation : public QWidget
{
    Q_OBJECT

public:
    explicit WindowPresentation(QWidget *parent = 0);
    ~WindowPresentation();

    QWebView *wV;

private:
    Ui::WindowPresentation *ui;
    bool testRegExpNumber(QString fr);//проверка для целых числе (int)
    bool testRegExpMark(QString mr); //проверка для знака
    bool testRegExpNumberDoub(QString fr);//проверка для десятичной дроби
    bool testRegExpNumberDoub17(QString fr);
    void checkHasText();
    void checkHasText2();
    bool isDataOk();
    void calc(FractionCalc a);
    QString lETotal1;
    QString lETotal2;
    QString lENum1;
    QString lENum2;
    QString lEDen1;
    QString lEDen2;
    QString lESign1;
    QString lESign2;
    QString lEDec1;
    QString lEDec2;


signals:
    void openMainWindow();
private slots:
    void on_pushButtonBack1_clicked();
    void on_pushButtonDemo_clicked();
    void on_lineEditTotal1_textChanged(const QString &arg1);
    void on_lineEditSign1_textChanged(const QString &arg1);
    void on_lineEditSign2_textChanged(const QString &arg1);
    void on_lineEditNumerator1_textChanged(const QString &arg1);
    void on_lineEditTotal2_textChanged(const QString &arg1);
    void on_lineEditNumerator2_textChanged(const QString &arg1);
    void on_lineEditDenominator1_textChanged(const QString &arg1);
    void on_lineEditDenominator2_textChanged(const QString &arg1);
    void on_lineEditDecimal1_textChanged(const QString &arg1);
    void on_lineEditDecimal2_textChanged(const QString &arg1);
};

#endif // WINDOWPRESENTATION_H
