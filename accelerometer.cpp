#include "accelerometer.h"
#include <QDebug>
#define calibrationDuration 1

Accelerometer::Accelerometer(QObject *parent) : QObject(parent)
{
    sensor = new QAccelerometer(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Accelerometer::onSensorReadingChanged);
}

Accelerometer::~Accelerometer()
{
    stop();
    delete sensor;
}

void Accelerometer::start()
{
    if (!sensor->isActive())
    {
        sensor->start();
        timer->start(1000);
        emit activeChanged();
        qDebug() << "Accelerometer started.";
    }
}

void Accelerometer::stop()
{
    if (sensor->isActive())
    {
        sensor->stop();
        timer->stop();
        emit activeChanged();
        qDebug() << "Accelerometer stopped.";
    }
}

void Accelerometer::onSensorReadingChanged()
{
    QAccelerometerReading *reading = sensor->reading();
    if (reading)
    {
        QString output = QStringLiteral("X: %1  Y: %2")
                             .arg(QString::number(reading->x(), 'f', 1),
                                  QString::number(reading->y(), 'f', 1));
        emit readingUpdated(output);
        qDebug() << output;
    }
    else
    {
        qDebug() << "No reading available.";
    }
}

void Accelerometer::Calibration()
{
    // Reset biases
    x_bias = 0.0;
    y_bias = 0.0;
    qreal calibrationSamples = 0;

    // Set up a timer to read sensor data for 1 second
    QTimer calibrateTimer;
    connect(&calibrateTimer, &QTimer::timeout, [&]() {
        // Read sensor data
        QAccelerometerReading *reading = sensor->reading();
        if (reading)
        {
            // Accumulate readings for x and y axes
            calibrationSamples += 1;
            x_bias += reading->x();
            y_bias += reading->y();
        }
    });

    // After 1 second, calculate biases and emit signal
    QObject::connect(&calibrateTimer, &QTimer::timeout, [&]() {
        // Calculate average biases
        x_bias /= calibrationSamples;
        y_bias /= calibrationSamples;

        // Emit signal with calibration results
        QString output = QStringLiteral("X bias: %1  Y bias: %2")
                             .arg(QString::number(x_bias, 'f', 1),
                                  QString::number(y_bias, 'f', 1));
        emit calibrationFinished(output);
    });

    // Start the timer
    calibrateTimer.setSingleShot(true);
    calibrateTimer.start(calibrationDuration * 1000); // Convert seconds to milliseconds
}

