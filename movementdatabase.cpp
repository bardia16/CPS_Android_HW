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
    /*qDebug() << "Velocities:";
    qDebug() << velocityX;
    qDebug() << velocityY;*/
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
    emit movementsUpdated(0.0, 0.0, 0.0);
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
    emit movementsUpdated(lastPosition.x(), lastPosition.y(), lastAngle);
    //qDebug() << "New update to positions";
    //qDebug() << lastPosition.y();
    m_movements.append(newMovement);
    currentMovement = newMovement;
}

QList<Movement *> MovementDatabase::movements() const
{
    return m_movements;
}
