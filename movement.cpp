#include "movement.h"
#include <QDebug>

Movement::Movement(QObject *parent)
    : QObject(parent), sampleInterval(0.01), currentAngle(0.0) // assuming a sample interval of 0.05 seconds
{
}

void Movement::addAcceleration(double x, double y)
{
    accelerations.append(QVector3D(x, y, 0.0));
}

void Movement::addAngleChange(double alpha)
{
    angleChanges.append(alpha);
    currentAngle = alpha;
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

        qreal distanceX = averageVelocityX * sampleInterval;
        qreal distanceY = averageVelocityY * sampleInterval;

        totalDistance += std::sqrt(distanceX * distanceX + distanceY * distanceY);

        previousVelocityX = velocityX;
        previousVelocityY = velocityY;
    }
    //qDebug() << totalDistance;
    return totalDistance;
}

void Movement::setStartPosition(qreal x, qreal y)
{
    startPosition = QVector3D(x, y, 0.0);
}

void Movement::setStartAngle(qreal angle)
{
    currentAngle = angle;
}

qreal Movement::calculateDistanceTraveledX() const
{
    qreal totalDistance = 0.0;
    qreal velocityX = 0.0;
    qreal previousVelocityX = 0.0;
    for (const QVector3D &acceleration : accelerations) {
        velocityX += acceleration.x() * sampleInterval;

        qreal averageVelocityX = (previousVelocityX + velocityX) / 2;

        qreal distanceX = averageVelocityX * sampleInterval;

        totalDistance += distanceX;

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

        qreal distanceY = averageVelocityY * sampleInterval;

        totalDistance += distanceY;

        previousVelocityY = velocityY;
    }
    return totalDistance;
}

QVector3D Movement::getCurrentPosition() const
{
    qreal distanceTraveledX = calculateDistanceTraveledX();
    qreal distanceTraveledY = calculateDistanceTraveledY();
    QVector3D currentPosition = startPosition;
    if (currentAngle == 0)
    {
        currentPosition.setX(startPosition.x() + distanceTraveledX);
        currentPosition.setY(startPosition.y() + distanceTraveledY);
    }
    else if (currentAngle == 90)
    {
        currentPosition.setX(startPosition.x() - distanceTraveledY);
        currentPosition.setY(startPosition.y() + distanceTraveledX);
    }
    else if (currentAngle == -90)
    {
        currentPosition.setX(startPosition.x() + distanceTraveledY);
        currentPosition.setY(startPosition.y() - distanceTraveledX);
    }
    else if (currentAngle == 180)
    {
        currentPosition.setX(startPosition.x() - distanceTraveledX);
        currentPosition.setY(startPosition.y() - distanceTraveledY);
    }

    currentPosition.setZ(0.0);
    qDebug() << "New starting position:";
    qDebug() << currentPosition;
    return currentPosition;
}

double Movement::getCurrentAngle() const
{
    return currentAngle;
}

void Movement::findDirection()
{
    qreal distanceX = calculateDistanceTraveledX();
    qreal distanceY = calculateDistanceTraveledY();
    bool main_direction_is_X = std::abs(distanceX) > std::abs(distanceY);
    qreal angle = getCurrentAngle();
    QString direction = "Not assigned";
    //logic

    if(main_direction_is_X && distanceX > 0)
    {
        if(angle == 0)
            direction = "Right";
        else if(angle == 90)
            direction = "Up";
        else if(angle == -90)
            direction = "Bottom";
        else if(angle == 180)
            direction = "Left";
    }
    else if(main_direction_is_X && distanceX < 0)
    {
        if(angle == 0)
            direction = "Left";
        else if(angle == 90)
            direction = "Bottom";
        else if(angle == -90)
            direction = "Up";
        else if(angle == 180)
            direction = "Right";
    }
    if(!main_direction_is_X && distanceY > 0)
    {
        if(angle == 0)
            direction = "Up";
        else if(angle == 90)
            direction = "Left";
        else if(angle == -90)
            direction = "Right";
        else if(angle == 180)
            direction = "Down";
    }
    else if(!main_direction_is_X && distanceY < 0)
    {
        if(angle == 0)
            direction = "Down";
        else if(angle == 90)
            direction = "Right";
        else if(angle == -90)
            direction = "Left";
        else if(angle == 180)
            direction = "Up";
    }



    currentDirection = direction;
}

QString Movement::getDirection() const
{
    return currentDirection;
}
