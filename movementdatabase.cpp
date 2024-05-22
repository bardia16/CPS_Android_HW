#include "movementdatabase.h"
#include <cmath>
#include <QDebug>

#define min_distance 0.2
MovementDatabase::MovementDatabase(QObject *parent)
    : QObject(parent), currentMovement(new Movement(this))
{
    m_movements.append(currentMovement);
}

void MovementDatabase::handleNewAcceleration(double x, double y, double velocityX, double velocityY, double xBias, double yBias)
{
    if (std::abs(x) <= min_acceleration && std::abs(y) <= min_acceleration && (std::abs(velocityX) <= min_velocity && std::abs(velocityY) <= min_velocity))
    {
        if(currentMovement->calculateDistanceTraveled() >= min_distance)
        {
            createNewMovement();
            qDebug() << "Creating new movements";
        }
        else if(currentMovement->calculateDistanceTraveled() < min_distance && currentMovement->calculateDistanceTraveled() > 0.0)
        {
            currentMovement->accelerations.clear();
            currentMovement->angleChanges.clear(); // no need to store because the movement was rotation
            qDebug() << "Movement cleared";
        }

    }

    if (std::abs(x) >= min_acceleration || std::abs(y) >= min_acceleration) {
        currentMovement->addAcceleration(x, y);
    }
    //qDebug() << m_movements;
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
    //emit movementsUpdated(0.0, 0.0, 0.0, "Reset");
    qDebug() << "MovementDatabase reset.";
}

void MovementDatabase::createNewMovement()
{
    QVector3D lastPosition;
    qreal lastAngle;
    Movement* newMovement = new Movement(this);
    Movement* lastMovement = m_movements.last();
    newMovement->setStartPosition(0.0, 0.0);
    newMovement->setStartAngle(0.0);
    lastPosition = QVector3D(0.0, 0.0, 0.0);
    lastAngle = 0.0;
    if (!m_movements.isEmpty()) {
        lastMovement->findDirection();
        lastPosition = lastMovement->getCurrentPosition();
        lastAngle = lastMovement->getCurrentAngle();
        newMovement->setStartPosition(lastPosition.x(), lastPosition.y());
        newMovement->setStartAngle(lastAngle);
    }
    emit movementsUpdated(lastPosition.x(), lastPosition.y(), lastAngle, lastMovement->getDirection());
    m_movements.append(newMovement);
    currentMovement = newMovement;
}

/*QString MovementDatabase::getDirection()
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
}*/

void MovementDatabase::createNewPattern(bool isAttempt)
{
    // Create a new Pattern instance with the current list of movements
    Pattern* pattern = new Pattern(m_movements, this);

    if(!isAttempt)
        emit newPattern(pattern);
    else
        emit newAttempt(pattern);

    // Optionally, clear the current list of movements if needed
    reset();
}
