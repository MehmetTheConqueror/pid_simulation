#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmath.h>
#include <QDebug>

#define PROCESS_PERIOD   100 // ms
#define NORMAL_CONDITION 25.0

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    process_value = NORMAL_CONDITION;
    power = 0;

    pid = create_pid(2, 0.1, 0.5, 1, PROCESS_PERIOD/1000.0);

    isSimStarted = false;
    timer = new QTimer(this);
    connect (timer, SIGNAL(timeout()), this, SLOT(timerTick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()        // start button
{
    if ( !isSimStarted ) {
        float kp = ui->lineKp->text().toFloat();
        float kd = ui->lineKd->text().toFloat();
        float ki = ui->lineKi->text().toFloat();

        set_value = ui->lineEdit->text().toFloat();

        pid_set_parameters(pid, kp, kd, ki);
        pid_reset(pid, set_value);

        isSimStarted = true;
        ui->pushButton->setText("Stop");
        timer->start(PROCESS_PERIOD);
    }
    else {
        isSimStarted = false;
        ui->pushButton->setText("Start");
        timer->stop();
    }
}

void MainWindow::timerTick()
{
    if (ui->checkBox->isChecked())  {  // manual
        power = ui->sldPower->value();
    }
    else {
        power = pid_calculate_output(pid, process_value);   // from pid calculation
        ui->sldPower->setValue(power);
    }

    calc_simulation();
    refreshScreen();
}

void MainWindow::refreshScreen()
{
    static bool prevTuningStat = false;

    ui->lblOutput->setText(QString::number(power, 'f', 2));
    ui->lblProcessValue->setText(QString::number(process_value, 'f', 2));

    if ( !pid->isTuning && prevTuningStat ) {
        ui->lineKd->setText(QString::number(pid->kd, 'f', 2));
        ui->lineKp->setText(QString::number(pid->kp, 'f', 2));
        ui->lineKi->setText(QString::number(pid->ki, 'f', 2));
    }

    prevTuningStat = pid->isTuning;
}

void MainWindow::calc_simulation()
{
//    float heating = 0;
//    if (power > 0){
//        heating = qPow( power, 0.3 );
//    }

//    float cooling = 0;
//    if (process_value > NORMAL_CONDITION)
//        cooling = qPow((process_value - NORMAL_CONDITION), 0.2);


//    process_value += (heating - cooling);

    static float reminder_energy = 0.0;

    float transfered_energy = power * 0.1 + reminder_energy * 0.01;
    float loosing_energy = (process_value - NORMAL_CONDITION);
    if ( loosing_energy < 0 )
        loosing_energy = 0;

    float total_delta_energy = transfered_energy - loosing_energy * 0.1;
    process_value += total_delta_energy;

    reminder_energy += (power * 0.9 - reminder_energy*0.02 );
    if (reminder_energy < 0)
        reminder_energy = 0;
}

void MainWindow::on_pushButton_2_clicked()
{
    pid_start_tuning(pid);
    set_value = ui->lineEdit->text().toFloat();
    pid_reset(pid, set_value);
    timer->start(PROCESS_PERIOD);
}
