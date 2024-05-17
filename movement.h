#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <QObject>
#include <QVector>
#include <QVector3D>

#define min_acceleration 0
#define min_velocity 0

class Movement : public QObject
{
    Q_OBJECT
public:
    explicit Movement(QObject *parent = nullptr);

    void addAcceleration(double x, double y);
    qreal calculateDistanceTraveled() const;
    qreal calculateDistanceTraveledX() const;
    qreal calculateDistanceTraveledY() const;
    QVector<QVector3D> accelerations;
    void setStartPosition(qreal x, qreal y);
    QVector3D getCurrentPosition() const;

private:
    QVector3D startPosition;
    qreal sampleInterval;
};

#endif // MOVEMENT_H
