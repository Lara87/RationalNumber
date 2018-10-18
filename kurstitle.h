#ifndef KURSTITLE_H
#define KURSTITLE_H

#include <QWidget>

namespace Ui {
class KursTitle;
}

class KursTitle : public QWidget
{
    Q_OBJECT

public:
    explicit KursTitle(QWidget *parent = 0);
    ~KursTitle();

private:
    Ui::KursTitle *ui;
    void keyPressEvent(QKeyEvent *);//метод получающий событие - нажатие enter

signals:
    void openMainWindow(); //создали сигнал
};

#endif // KURSTITLE_H
