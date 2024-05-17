#include "movement.h"
#include <QDebug>

Movement::Movement(QObject *parent)
    : QObject(parent), sampleInterval(0.005), currentAngle(0.0) // assuming a sample interval of 0.25 seconds
{
}

void Movement::addAcceleration(double x, double y)
{
    accelerations.append(QVector3D(x, y, 0.0));
}

void Movement::addAngleChange(double alpha)
{
    currentAngle += alpha;
    // Ensure the angle stays within the range of 0 to 360 degrees
    if (currentAngle >= 360.0) currentAngle -= 360.0;
    if (currentAngle < 0.0) currentAngle += 360.0;
}

qreal Movement::calculateDistanceTraveled() const
{
    qreal totalDistance = 0.0;
    qreal velocityX = 0.0;
    qreal velocityY = 0.0;
    qreal previousVelocityX = 0.0;
    qreal previousVelocityY = 0.0;
    for (const QVector3D &acceleration : accelerations) {
        velocityX += acceleration.x() * sampleInterval;
        velocityY += acceleration.y() * sampleInterval;

        qreal averageVelocityX = (previousVelocityX + velocityX) / 2;
        qreal averageVelocityY = (previousVelocityY + velocityY) / 2;

        // Calculate the distance traveled in this sample interval
        qreal distanceX = averageVelocityX * sampleInterval;
        qreal distanceY = averageVelocityY * sampleInterval;

        totalDistance += std::sqrt(distanceX * distanceX + distanceY * distanceY);

        // Update previous velocities for the next iteration
        previousVelocityX = velocityX;
        previousVelocityY = velocityY;
    }
    qDebug() << totalDistance;
    return totalDistance;
}

void Movement::setStartPosition(qreal x, qreal y)
{
    startPosition = QVector3D(x, y, 0.0);
}

qreal Movement::calculateDistanceTraveledX() const
{
    qreal totalDistance = 0.0;
    qreal velocityX = 0.0;
    qreal previousVelocityX = 0.0;
    for (const QVector3D &acceleration : accelerations) {
        velocityX += acceleration.x() * sampleInterval;

        qreal averageVelocityX = (previousVelocityX + velocityX) / 2;

        // Calculate the distance traveled in this sample interval
        qreal distanceX = averageVelocityX * sampleInterval;

        totalDistance += distanceX;

        // Update previous velocities for the next iteration
        previousVelocityX = velocityX;
    }
    return totalDistance;
}

qreal Movement::calculateDistanceTraveledY() const
{
    qreal totalDistance = 0.0;
    qreal velocityY = 0.0;
    qreal previousVelocityY = 0.0;
    for (const QVector3D &acceleration : accelerations) {
        velocityY += acceleration.y() * sampleInterval;

        qreal averageVelocityY = (previousVelocityY + velocityY) / 2;

        // Calculate the distance traveled in this sample interval
        qreal distanceY = averageVelocityY * sampleInterval;

        totalDistance += distanceY;

        // Update previous velocities for the next iteration
        previousVelocityY = velocityY;
    }
    return totalDistance;
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

double Movement::getCurrentAngle() const
{
    return currentAngle;
}
