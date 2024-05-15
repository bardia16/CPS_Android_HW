#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <QObject>
#include <QtSensors/QAccelerometer>
#include <QTimer>
#include <QTextBrowser>

class Accelerometer : public QObject
{
    Q_OBJECT
public:
    explicit Accelerometer(QObject *parent = nullptr);
    ~Accelerometer();

public slots:
    void start();
    void stop();

signals:
    void readingUpdated(const QString &output);

private slots:
    void onSensorReadingChanged();

private:
    QAccelerometer *sensor;
    QTimer *timer;
};

#endif // ACCELEROMETER_H
