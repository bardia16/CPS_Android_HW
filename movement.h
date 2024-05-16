#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <QObject>
#include <QVector3D>
#include <QList>

class Movement : public QObject
{
    Q_OBJECT
public:
    explicit Movement(QObject *parent = nullptr);
    void addAcceleration(const QVector3D &acceleration);
    qreal calculateDistanceTraveled() const;
    QVector3D getLastAcceleration() const;
    bool checkForNewMovement() const;
    //bool checkForNewAcceleration() const;

private:
    QList<QVector3D> accelerations;
    qreal acceleration_threshold;
    qreal sampling_interval = 0.1;
};

#endif // MOVEMENT_H
