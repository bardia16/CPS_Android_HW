#include "movementdatabase.h"
#include <cmath>
#include <QDebug>

#define min_distance 0.1
MovementDatabase::MovementDatabase(QObject *parent)
    : QObject(parent), currentMovement(new Movement(this))
{
    m_movements.append(currentMovement);
}

void MovementDatabase::handleNewAcceleration(double x, double y, double velocityX, double velocityY, double xBias, double yBias)
{
    if (std::abs(x) <= min_acceleration && std::abs(y) <= min_acceleration && currentMovement->calculateDistanceTraveled() > min_distance
        && (std::abs(velocityX) <= min_velocity && std::abs(velocityY) <= min_velocity))
    {
        createNewMovement();
        qDebug() << "Creating new movements";
    }
    if (std::abs(x) >= min_acceleration || std::abs(y) >= min_acceleration) {
        currentMovement->addAcceleration(x, y);
    }
    qDebug() << m_movements;
}

void MovementDatabase::handleNewAngle(double alpha)
{
    currentMovement->addAngleChange(alpha);
    emit angleUpdated(currentMovement->getCurrentAngle());
}

void MovementDatabase::reset()
{
    currentMovement = new Movement(this);
    m_movements.clear();
    m_movements.append(currentMovement);
    emit movementsUpdated(0.0, 0.0, 0.0, "Reset");
    qDebug() << "MovementDatabase reset.";
}

void MovementDatabase::createNewMovement()
{
    QVector3D lastPosition;
    qreal lastAngle;
    Movement* newMovement = new Movement(this);
    newMovement->setStartPosition(0.0, 0.0);
    newMovement->setStartAngle(0.0);
    lastPosition = QVector3D(0.0, 0.0, 0.0);
    lastAngle = 0.0;
    if (!m_movements.isEmpty()) {
        lastPosition = m_movements.last()->getCurrentPosition();
        lastAngle = m_movements.last()->getCurrentAngle();
        newMovement->setStartPosition(lastPosition.x(), lastPosition.y());
        newMovement->setStartAngle(lastAngle);
    }
    emit movementsUpdated(lastPosition.x(), lastPosition.y(), lastAngle, getDirection());
    m_movements.append(newMovement);
    currentMovement = newMovement;
}

QString MovementDatabase::getDirection()
{
    qreal distanceX = currentMovement->calculateDistanceTraveledX();
    qreal distanceY = currentMovement->calculateDistanceTraveledY();
    bool main_direction_is_X = std::abs(distanceX) > std::abs(distanceY);
    qreal angle = currentMovement->getCurrentAngle();
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




    return direction;
}

QList<Movement *> MovementDatabase::movements() const
{
    return m_movements;
}
