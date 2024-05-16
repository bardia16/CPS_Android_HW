#include "movement.h"

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
    return distance;
}
