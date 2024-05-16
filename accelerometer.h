#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <QObject>
#include <QtSensors/QAccelerometer>
#include <QTimer>
#include <QVector>

#define calibrationDuration 1000 // 1sec
#define sampling_interval 100 // 100ms

class Accelerometer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool active READ isActive NOTIFY activeChanged)

public:
    explicit Accelerometer(QObject *parent = nullptr);
    ~Accelerometer();

    bool isActive() const { return sensor->isActive(); }

    Q_INVOKABLE double getXBias() const { return x_bias; }
    Q_INVOKABLE double getYBias() const { return y_bias; }

public slots:
    void start();
    void stop();
    void calibration();

signals:
    void readingUpdated(const QString &output);
    void activeChanged();
    void calibrationFinished(const QString &output);
    void newAcceleration(double x, double y);

private slots:
    void onSensorReadingChanged();
    void onCalibrationReadingChanged();
    void onCalibrationFinished();

private:
    QAccelerometer *sensor;
    QTimer *timer;
    QTimer *calibrationTimer;
    QVector<double> x_values;
    QVector<double> y_values;
    double x_bias;
    double y_bias;
};

#endif // ACCELEROMETER_H
