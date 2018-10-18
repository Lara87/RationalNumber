#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windowteoriya.h>
#include <windowpresentation.h>
#include <kurstitle.h>
#include <windowtesting.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonTeoriya_clicked();

    void on_pushButtonExit_clicked();

    void on_pushButtonDemo_clicked();

    void on_pushButtonTesting_clicked();

private:
    Ui::MainWindow *ui;

    WindowTeoriya *windowT;//создали объект нового окна - от windowteoriya

    WindowPresentation *windowP;//создали объект нового окна - от windowpresentation

    KursTitle *kursT;//создали объект нового окна - от kurstitle

    WindowTesting *windowTs;

};

#endif // MAINWINDOW_H
