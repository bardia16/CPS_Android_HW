#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <QObject>
#include <QtSensors/QAccelerometer>
#include <QTimer>

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


signals:
    void readingUpdated(const QString &output);
    void activeChanged();
    void calibrationFinished(QString &output);

private slots:
    void onSensorReadingChanged();
    void Calibration();


private:
    QAccelerometer *sensor;
    QTimer *timer;
    qreal x_bias;
    qreal y_bias;
};

#endif // ACCELEROMETER_H
