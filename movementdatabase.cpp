#include "movementdatabase.h"
#include <cmath>
#include <QDebug>

MovementDatabase::MovementDatabase(QObject *parent)
    : QObject(parent), currentMovement(new Movement(this))
{
    m_movements.append(currentMovement);
}

void MovementDatabase::handleNewAcceleration(double x, double y, double xBias, double yBias)
{
    if (std::abs(x) <= std::abs(xBias) && std::abs(y) <= std::abs(yBias) && currentMovement->accelerations.size() > 0)
    {
        currentMovement = new Movement(this);
        m_movements.append(currentMovement);
        emit movementsUpdated();
        qDebug() << "Creating new movements";
    }
    if (std::abs(x) > std::abs(xBias) || std::abs(y) > std::abs(yBias)) {
        currentMovement->addAcceleration(x, y);
    }
    qDebug() << currentMovement->accelerations;

}

QList<Movement *> MovementDatabase::movements() const
{
    return m_movements;
}
