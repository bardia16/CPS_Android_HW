#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <QObject>
#include <QtSensors/QGyroscope>
#include <QTimer>

#define calibrationDuration 1000 // 1 second
#define gyro_sampling_interval 10 // 10 ms
#define gyro_threshold 0.5 // Threshold for gyro noise

class GyroscopeKalmanFilter
{
public:
    GyroscopeKalmanFilter(double processNoise, double measurementNoise, double estimationError, double initialValue)
        : q(processNoise), r(measurementNoise), p(estimationError), x(initialValue) {}

    double update(double measurement)
    {
        // Prediction update
        p = p + q;

        // Measurement update
        double k = p / (p + r); // Kalman gain
        x = x + k * (measurement - x); // Update estimate
        p = (1 - k) * p; // Update error covariance

        return x;
    }

    void reset(double initialValue)
    {
        p = q;
        x = initialValue;
    }

private:
    double q; // Process noise covariance
    double r; // Measurement noise covariance
    double p; // Estimation error covariance
    double x; // Value
};

class Gyroscope : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool active READ isActive NOTIFY activeChanged)

public:
    explicit Gyroscope(QObject *parent = nullptr);
    ~Gyroscope();

    bool isActive() const { return sensor->isActive(); }

    Q_INVOKABLE void calibration();
    Q_INVOKABLE void reset();

public slots:
    void start();
    void stop();

signals:
    void readingUpdated(const QString &output);
    void activeChanged();
    void calibrationFinished(const QString &output);
    void newRotation(double alpha);

private slots:
    void onSensorReadingChanged();
    void onCalibrationReadingChanged();
    void onCalibrationFinished();

private:
    QGyroscope *sensor;
    QTimer *timer;
    QTimer *calibrationTimer;
    QVector<double> z_values;
    double z_bias;
    double currentAngle;
    GyroscopeKalmanFilter angleKalman;
};

#endif // GYROSCOPE_H
