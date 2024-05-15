#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartRecording_clicked()
{
    // Check the current text of the button and swap it
    if (ui->StartRecording->text() == "Start Recording") {
        ui->StartRecording->setText("Stop Recording");
    } else {
        ui->StartRecording->setText("Start Recording");
    }
}



void MainWindow::on_StartAttempt_clicked()
{
    // Check the current text of the button and swap it
    if (ui->StartAttempt->text() == "Start Attempt") {
        ui->StartAttempt->setText("Stop Attempt");
    } else {
        ui->StartAttempt->setText("Start Attempt");
    }
}

