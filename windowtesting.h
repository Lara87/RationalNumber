#ifndef WINDOWTESTING_H
#define WINDOWTESTING_H

#include <QWidget>
#include <QRadioButton>

struct SetRadioButtons
{
    QRadioButton *button1;
    QRadioButton *button2;
    QRadioButton *button3;
};

struct TestQuestion
{
    QString question;
    SetRadioButtons setRadioButtonsList;
    int answerIndex;

};

namespace Ui {
class WindowTesting;
}

class WindowTesting : public QWidget
{
    Q_OBJECT

public:
    explicit WindowTesting(QWidget *parent = 0);
    ~WindowTesting();
    virtual void closeEvent(QCloseEvent *event);//подписываемся на событие
private slots:
    void on_pushButtonBack_clicked();

    void on_pushButtonTestEnd_clicked();

private:
    Ui::WindowTesting *ui;
    QString readFile();
    void parse(QString que);
    QList <TestQuestion> book;
    int bookIndex;
    int rightAnswer();
    bool checkRadioButton(TestQuestion a);
    bool writeResultRightAnswer(int);
    bool testRegUserName(QString fr);

signals:
    void openMainWindow(); //создали сигнал
};

#endif // WINDOWTESTING_H
