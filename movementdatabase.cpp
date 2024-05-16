#include "movementdatabase.h"
#include <cmath>
#include <QDebug>

#define min_distance 0.01
MovementDatabase::MovementDatabase(QObject *parent)
    : QObject(parent), currentMovement(new Movement(this))
{
    m_movements.append(currentMovement);
}

void MovementDatabase::handleNewAcceleration(double x, double y, double velocityX, double velocityY, double xBias, double yBias)
{
    qDebug() << "Velocities:";
    qDebug() << velocityX;
    qDebug() << velocityY;
    if (std::abs(x) < min_acceleration && std::abs(y) < min_acceleration && currentMovement->calculateDistanceTraveled() > min_distance
        && (std::abs(velocityX) < min_velocity && std::abs(velocityY) < min_velocity))
    {
        //qreal dist = currentMovement->calculateDistanceTraveled();
        createNewMovement();
        qDebug() << "Creating new movements";
    }
    if (std::abs(x) >= min_acceleration || std::abs(y) >= min_acceleration) {
        currentMovement->addAcceleration(x, y);
    }
    qDebug() << m_movements;

}

void MovementDatabase::createNewMovement()
{
    Movement* newMovement = new Movement(this);
    newMovement->setStartPosition(0.0, 0.0);
    if (!m_movements.isEmpty()) {
        QVector3D lastPosition = m_movements.last()->getCurrentPosition();
        newMovement->setStartPosition(lastPosition.x(), lastPosition.y());
    }
    m_movements.append(newMovement);
    currentMovement = newMovement;
    emit movementsUpdated();
}

QList<Movement *> MovementDatabase::movements() const
{
    return m_movements;
}
