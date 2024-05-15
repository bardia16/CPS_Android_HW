#include "accelerometer.h"
#include <QDebug>

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
        QString output = QStringLiteral("X: %1\nY: %2\nZ: %3")
                             .arg(QString::number(reading->x(), 'f', 1),
                                  QString::number(reading->y(), 'f', 1),
                                  QString::number(reading->z(), 'f', 1));
        emit readingUpdated(output);
        qDebug() << output;
    }
    else
    {
        qDebug() << "No reading available.";
    }
}
