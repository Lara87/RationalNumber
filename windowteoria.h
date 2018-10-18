#ifndef WINDOWTEORIYA_H
#define WINDOWTEORIYA_H

#include <QWidget>

namespace Ui {
class WindowTeoriya;
}

class WindowTeoriya : public QWidget
{
    Q_OBJECT

public:
    explicit WindowTeoriya(QWidget *parent = 0);
    ~WindowTeoriya();

private slots:
    void on_pushButtonNext_clicked();

    void on_pushButtonPrev_clicked();

    void on_pushButtonBack_clicked();

private:
    Ui::WindowTeoriya *ui;
    QString loadFile();
    QList <QString> parse(QString s);
    QList <QString> book;
    int bookIndex;

signals:
    void openMainWindow(); //создали сигнал

};

#endif // WINDOWTEORIYA_H
