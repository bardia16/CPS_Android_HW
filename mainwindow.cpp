#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "accelerometer.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , accelerometer(nullptr)
{
    ui->setupUi(this);
    ui->accel_text->setUpdatesEnabled(true);
    // Set the background color of textBrowser to dark gray and text color to white
    ui->accel_text->setStyleSheet("background-color: darkgray; color: white;");
    ui->textBrowser_2->setStyleSheet("background-color: darkgray; color: white;");
    ui->listView->setStyleSheet("background-color: darkgray; color: white;");

    accelerometer = new Accelerometer(this);
    connect(accelerometer, &Accelerometer::readingUpdated, this, &MainWindow::updateTextBrowser);
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
        accelerometer->start();  // Start accelerometer readings
    } else {
        ui->StartRecording->setText("Start Recording");
        accelerometer->stop();   // Stop accelerometer readings
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

void MainWindow::updateTextBrowser(const QString &output)
{
    ui->accel_text->setText(QString(""));
    ui->accel_text->setText(output);
    qDebug() << "text updated";
    ui->accel_text->repaint();
}
