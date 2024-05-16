#include "accelerometer.h"
#include <QDebug>

Accelerometer::Accelerometer(QObject *parent) : QObject(parent), x_bias(0.0), y_bias(0.0)
{
    sensor = new QAccelerometer(this);
    timer = new QTimer(this);
    calibrationTimer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Accelerometer::onSensorReadingChanged);
    connect(calibrationTimer, &QTimer::timeout, this, &Accelerometer::onCalibrationFinished);
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
        timer->start(sampling_interval);
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
        calibrationTimer->stop();
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
        emit newAcceleration(reading->x(), reading->y());
        qDebug() << output;
    }
    else
    {
        qDebug() << "No reading available.";
    }
}

void Accelerometer::calibration()
{
    sensor->start();
    x_values.clear();
    y_values.clear();
    calibrationTimer->start(calibrationDuration);
    connect(sensor, &QAccelerometer::readingChanged, this, &Accelerometer::onCalibrationReadingChanged);
}

void Accelerometer::onCalibrationReadingChanged()
{
    QAccelerometerReading *reading = sensor->reading();
    if (reading)
    {
        x_values.append(reading->x());
        y_values.append(reading->y());
    }
    else
    {
        qDebug() << "No reading available.";
    }
}

void Accelerometer::onCalibrationFinished()
{
    sensor->stop();
    calibrationTimer->stop();
    disconnect(sensor, &QAccelerometer::readingChanged, this, &Accelerometer::onCalibrationReadingChanged);

    double x_sum = 0.0;
    double y_sum = 0.0;

    for (double x : x_values)
        x_sum += x;

    for (double y : y_values)
        y_sum += y;

    x_bias = x_sum / x_values.size();
    y_bias = y_sum / y_values.size();

    QString output = QStringLiteral("Calibration complete\tX bias: %1 Y bias: %2")
                         .arg(QString::number(x_bias, 'f', 1),
                              QString::number(y_bias, 'f', 1));
    qDebug() << "Biases: " + output;

    emit calibrationFinished(output);
}
