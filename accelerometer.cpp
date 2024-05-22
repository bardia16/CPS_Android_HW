#include "accelerometer.h"
#include <QDebug>

Accelerometer::Accelerometer(QObject *parent) : QObject(parent), x_bias(0.0), y_bias(0.0),
    xKalman(0.1, 1, 0.1, 0.0), yKalman(0.1, 1, 0.1, 0.0), velocity(0.0),velocityX(0.0), velocityY(0.0) // Initialize Kalman filters
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
        timer->start(accel_sampling_interval);
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
        qreal x = reading->x();
        qreal y = reading->y();



        // Apply Kalman filter
        x = xKalman.update(x);
        y = yKalman.update(y);

        // Adjust for bias
        if (std::abs(x) <= accel_threshold)
            x = 0.0;
        else
            x -= x_bias;

        if (std::abs(y) <= accel_threshold)
            y = 0.0;
        else
            y -= y_bias;

        if (x == 0 && y == 0) // frictional accel
        {
            QVector2D newVelocities = frictionalAccel(velocityX, velocityY);
            velocityX = newVelocities.x();
            velocityY = newVelocities.y();

        }

        velocityX += x * accel_sampling_interval/1000;
        velocityY += y * accel_sampling_interval/1000;
        //velocity += std::sqrt(velocityX * velocityX + velocityY * velocityY);

        QString output = QStringLiteral("X: %1  Y: %2  Velocity: X: %3  Y: %4")
                             .arg(QString::number(x, 'f', 2),
                                  QString::number(y, 'f', 2),
                                  QString::number(velocityX, 'f', 2),
                                  QString::number(velocityY, 'f', 2));
        emit readingUpdated(output);
        emit newAcceleration(x, y, velocityX, velocityY);
        //qDebug() << output;
    }
    else
    {
        qDebug() << "No reading available.";
    }
}

QVector2D Accelerometer::frictionalAccel(qreal velocityX, qreal velocityY)
{
    qreal frictionalDecay = accel_threshold * accel_sampling_interval / 1000;

    if (velocityX > 0) // If velocityX is positive
    {
        velocityX -= frictionalDecay;
        if (velocityX < 0) // Ensure velocity doesn't go negative
            velocityX = 0;
    }
    else if (velocityX < 0) // If velocityX is negative
    {
        velocityX += frictionalDecay;
        if (velocityX > 0) // Ensure velocity doesn't go positive
            velocityX = 0;
    }

    if (velocityY > 0) // If velocityY is positive
    {
        velocityY -= frictionalDecay;
        if (velocityY < 0) // Ensure velocity doesn't go negative
            velocityY = 0;
    }
    else if (velocityY < 0) // If velocityY is negative
    {
        velocityY += frictionalDecay;
        if (velocityY > 0) // Ensure velocity doesn't go positive
            velocityY = 0;
    }

    return QVector2D(velocityX, velocityY);
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
