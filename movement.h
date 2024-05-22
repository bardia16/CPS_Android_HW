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
    void addAngleChange(double alpha);
    qreal calculateDistanceTraveled() const;
    qreal calculateDistanceTraveledX() const;
    qreal calculateDistanceTraveledY() const;
    QVector<QVector3D> accelerations;
    QVector<double> angleChanges;
    void setStartPosition(qreal x, qreal y);
    void setStartAngle(qreal angle);
    QVector3D getCurrentPosition() const;
    double getCurrentAngle() const;
    QString getDirection() const;
    void findDirection();

private:
    QVector3D startPosition;
    qreal sampleInterval;
    double currentAngle;
    QString currentDirection;
};

#endif // MOVEMENT_H
