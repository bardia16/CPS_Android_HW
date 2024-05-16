#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , accelerometer(nullptr)
    , currentMovement(nullptr)
{
    ui->setupUi(this);

    // Initialize accelerometer
    accelerometer = new Accelerometer(this);
    connect(accelerometer, &Accelerometer::readingUpdated, this, &MainWindow::updateTextBrowser);
    connect(accelerometer, &Accelerometer::newAcceleration, this, &MainWindow::addMovement);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMovement(const QVector3D &acceleration)
{
    // If no movement exists or the last movement's acceleration is below the threshold, add a new movement
    if (movements.isEmpty() || (currentMovement && currentMovement->checkForNewMovement())) {
        currentMovement = new Movement(this);
        movements.append(currentMovement);
        qDebug() << "New movement created";
    }
    addAcceleration(acceleration);
}


void MainWindow::addAcceleration(const QVector3D &acceleration)
{
    if (currentMovement) {
        currentMovement->addAcceleration(acceleration);
        qDebug() << "Acceleration added";
    }
}

void MainWindow::updateTextBrowser(const QString &output)
{
    ui->accel_text->setText(output);
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
