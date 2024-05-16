#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <QObject>
#include <QtSensors/QAccelerometer>
#include <QTimer>
#include <QTextBrowser>
#include <QVector3D>

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
    void newAcceleration(const QVector3D &acceleration); // Added signal declaration

private slots:
    void onSensorReadingChanged();

private:
    QAccelerometer *sensor;
    QTimer *timer;
    bool checkForNewAcceleration(const QVector3D &acceleration) const;
};

#endif // ACCELEROMETER_H
