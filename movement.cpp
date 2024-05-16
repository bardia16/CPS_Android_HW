#include "movement.h"
#include <QDebug>
Movement::Movement(QObject *parent)
    : QObject(parent), sampleInterval(0.1) // assuming a sample interval of 0.1 seconds
{
}

void Movement::addAcceleration(double x, double y)
{
    accelerations.append(QVector3D(x, y, 0.0));
}

qreal Movement::calculateDistanceTraveled() const
{
    qreal distance = 0.0;
    for (const QVector3D &acceleration : accelerations) {

        // Assuming constant acceleration during the sample interval
        qreal distanceX = 0.5 * acceleration.x() * sampleInterval * sampleInterval;
        qreal distanceY = 0.5 * acceleration.y() * sampleInterval * sampleInterval;
        distance += qSqrt(distanceX * distanceX + distanceY * distanceY);
    }
    qDebug() << distance;
    return distance;
}


void Movement::setStartPosition(qreal x, qreal y)
{
    startPosition = QVector3D(x, y, 0.0);
}

qreal Movement::calculateDistanceTraveledX() const
{
    qreal distance = 0.0;
    for (const QVector3D &acceleration : accelerations) {
        qreal distanceX = 0.5 * acceleration.x() * sampleInterval * sampleInterval;
        distance += distanceX;
    }
    return distance;
}

qreal Movement::calculateDistanceTraveledY() const
{
    qreal distance = 0.0;
    for (const QVector3D &acceleration : accelerations) {
        qreal distanceY = 0.5 * acceleration.y() * sampleInterval * sampleInterval;
        distance += distanceY;
    }
    return distance;
}

QVector3D Movement::getCurrentPosition() const
{
    qreal distanceTraveledX = calculateDistanceTraveledX();
    qreal distanceTraveledY = calculateDistanceTraveledY();
    QVector3D currentPosition = startPosition;
    currentPosition.setX(startPosition.x() + distanceTraveledX);
    currentPosition.setY(startPosition.y() + distanceTraveledY);
    currentPosition.setZ(0.0);
    qDebug() << "New starting position:";
    qDebug() << currentPosition;
    return currentPosition;
}
