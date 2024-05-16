#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <QObject>
#include <QtSensors/QAccelerometer>
#include <QTimer>
#include <QVector>

class Accelerometer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool active READ isActive NOTIFY activeChanged)

public:
    explicit Accelerometer(QObject *parent = nullptr);
    ~Accelerometer();

    bool isActive() const { return sensor->isActive(); }

public slots:
    void start();
    void stop();
    void calibration();

signals:
    void readingUpdated(const QString &output);
    void activeChanged();
    void calibrationFinished(const QString &output);

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
};

#endif // ACCELEROMETER_H
