#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>


extern "C" {
  #include "pid.h"
}


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
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    pid_controller *pid;

    float process_value, set_value;
    float power = 0;
    void calc_simulation();

    void refreshScreen();

    bool isSimStarted;

private slots:
    void timerTick();
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
