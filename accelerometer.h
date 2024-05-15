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

private slots:
    void onSensorReadingChanged();

private:
    QAccelerometer *sensor;
    QTimer *timer;
};

#endif // ACCELEROMETER_H
