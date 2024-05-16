#include "movement.h"
#include <QtMath>
#include <QDebug>
Movement::Movement(QObject *parent)
    : QObject(parent)
{
}

void Movement::addAcceleration(const QVector3D &acceleration)
{
    accelerations.append(acceleration);
}

qreal Movement::calculateDistanceTraveled() const
{
    qreal distance = 0.0;
    for (const QVector3D &acceleration : accelerations) {
        // Assuming constant acceleration during the sample interval
        qreal distanceX = 0.5 * acceleration.x() * sampling_interval * sampling_interval;
        qreal distanceY = 0.5 * acceleration.y() * sampling_interval * sampling_interval;
        distance += qSqrt(distanceX * distanceX + distanceY * distanceY);
    }
    return distance;
}

QVector3D Movement::getLastAcceleration() const
{
    if (!accelerations.isEmpty())
        return accelerations.last();
    else
        return QVector3D();
}

bool Movement::checkForNewMovement() const
{
    qDebug() << "Checking for new movment";
    return !accelerations.isEmpty() &&
           qAbs(getLastAcceleration().x()) <= acceleration_threshold &&
           qAbs(getLastAcceleration().y()) <= acceleration_threshold;
}

/*bool Movement::checkForNewAcceleration() const
{
    return !accelerations.isEmpty() &&
           (qAbs(getLastAcceleration().x()) > acceleration_threshold ||
            qAbs(getLastAcceleration().y()) > acceleration_threshold);
}*/
