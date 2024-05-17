#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <QObject>
#include <QtSensors/QGyroscope>
#include <QTimer>

#define sampling_interval 5 // 5ms = 0.005sec

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

public slots:
    void start();
    void stop();
    void reset();

signals:
    void readingUpdated(const QString &output);
    void activeChanged();
    void newRotation(double alpha);
    void gyroscopeReset();

private slots:
    void onSensorReadingChanged();

private:
    QGyroscope *sensor;
    QTimer *timer;
    double alpha; // Rotation around the Z axis
    GyroscopeKalmanFilter alphaKalman; // Kalman filter for the Z axis
};

#endif // GYROSCOPE_H
