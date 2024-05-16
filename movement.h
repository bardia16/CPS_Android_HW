#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <QObject>
#include <QVector>
#include <QVector3D>

class Movement : public QObject
{
    Q_OBJECT
public:
    explicit Movement(QObject *parent = nullptr);

    void addAcceleration(double x, double y);
    qreal calculateDistanceTraveled() const;
    QVector<QVector3D> accelerations; // Make this public or add a getter

private:
    qreal sampleInterval;
};

#endif // MOVEMENT_H
