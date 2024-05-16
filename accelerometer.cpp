#include "accelerometer.h"
#include <QDebug>

#define sampling_interval 0.1
#define accelerationThreshold 0.2

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
        timer->start(sampling_interval * 1000);
        qDebug() << "Accelerometer started.";
    }
}

void Accelerometer::stop()
{
    if (sensor->isActive())
    {
        sensor->stop();
        timer->stop();
        qDebug() << "Accelerometer stopped.";
    }
}

bool Accelerometer::checkForNewAcceleration(const QVector3D &acceleration) const
{
    return qAbs(acceleration.x()) > accelerationThreshold || qAbs(acceleration.y()) > accelerationThreshold;
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
        if (checkForNewAcceleration(QVector3D(reading->x(), reading->y(), reading->z()))) {
            emit newAcceleration(QVector3D(reading->x(), reading->y(), reading->z())); // Emit new acceleration
        }
        qDebug() << output;
    }
    else
    {
        qDebug() << "No reading available.";
    }
}
