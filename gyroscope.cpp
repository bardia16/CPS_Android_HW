#include "gyroscope.h"
#include <QDebug>

Gyroscope::Gyroscope(QObject *parent)
    : QObject(parent), z_bias(0.0), currentAngle(0.0), angleKalman(0.1, 1, 0.1, 0.0) // Initialize Kalman filter
{
    sensor = new QGyroscope(this);
    timer = new QTimer(this);
    calibrationTimer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Gyroscope::onSensorReadingChanged);
    connect(calibrationTimer, &QTimer::timeout, this, &Gyroscope::onCalibrationFinished);
}

Gyroscope::~Gyroscope()
{
    stop();
    delete sensor;
}

void Gyroscope::start()
{
    if (!sensor->isActive())
    {
        currentAngle = 0.0; // reset it
        sensor->start();
        timer->start(gyro_sampling_interval);
        emit activeChanged();
        qDebug() << "Gyroscope started.";
    }
}

void Gyroscope::stop()
{
    if (sensor->isActive())
    {
        sensor->stop();
        timer->stop();
        calibrationTimer->stop();
        emit activeChanged();
        qDebug() << "Gyroscope stopped.";
    }
}

void Gyroscope::calibration()
{
    sensor->start();
    z_values.clear();
    calibrationTimer->start(calibrationDuration);
    connect(sensor, &QGyroscope::readingChanged, this, &Gyroscope::onCalibrationReadingChanged);
}

void Gyroscope::onCalibrationReadingChanged()
{
    QGyroscopeReading *reading = sensor->reading();
    if (reading)
    {
        z_values.append(reading->z());
    }
    else
    {
        qDebug() << "No reading available.";
    }
}

void Gyroscope::onCalibrationFinished()
{
    sensor->stop();
    calibrationTimer->stop();
    disconnect(sensor, &QGyroscope::readingChanged, this, &Gyroscope::onCalibrationReadingChanged);

    double z_sum = 0.0;
    for (double z : z_values)
        z_sum += z;

    z_bias = z_sum / z_values.size();

    QString output = QStringLiteral("Calibration complete\tZ bias: %1")
                         .arg(QString::number(z_bias, 'f', 1));
    qDebug() << "Bias: " + output;

    emit calibrationFinished(output);
}

void Gyroscope::onSensorReadingChanged()
{
    QGyroscopeReading *reading = sensor->reading();
    if (reading)
    {
        double alpha = reading->z();

        // Apply Kalman filter
        alpha = angleKalman.update(alpha);

        // Adjust for bias
        alpha -= z_bias;

        // Apply threshold
        if (std::abs(alpha) < gyro_threshold)
            alpha = 0.0;

        double angleChange = alpha * 0.01;
        currentAngle += angleChange;


        if (currentAngle >= 360.0) currentAngle -= 360.0;
        if (currentAngle < 0.0) currentAngle += 360.0;

        // Normalize the angle change
        double normalizedAngle = 0.0;
        if (currentAngle >= 60.0 && currentAngle < 135.0) {
            normalizedAngle = 90.0;
        } else if (currentAngle >= 135.0 && currentAngle < 225.0) {
            normalizedAngle = 180.0;
        } else if (currentAngle >= 225.0 && currentAngle < 315.0) {
            normalizedAngle = -90.0;
        } else {
            normalizedAngle = 0.0;
        }

        QString output = QStringLiteral("Alpha: %1").arg(QString::number(normalizedAngle, 'f', 2));

        emit readingUpdated(output);
        emit newRotation(normalizedAngle);

    }
    else
    {
        qDebug() << "No reading available.";
    }
}

void Gyroscope::reset()
{
    //z_bias = 0.0;
    currentAngle = 0.0;
    //angleKalman.reset(0.0);
    qDebug() << "Gyroscope reset.";
}
