#include "pattern.h"
#include <cmath>

Pattern::Pattern(const QList<Movement*> &movements, QObject *parent)
    : QObject(parent), m_movements(movements)
{
}

bool Pattern::authenticate(Pattern *other) const
{
    if (m_movements.size() != other->m_movements.size())
        return false;

    for (int i = 0; i < m_movements.size() - 1; ++i) {
        Movement* m1 = m_movements[i];
        Movement* m2 = other->m_movements[i];

        if (std::abs(m1->getCurrentAngle() - m2->getCurrentAngle()) > 0.0)
            return false;
        if (m1->getDirection() != m2->getDirection())
            return false;
        QVector3D pos1 = m1->getCurrentPosition();
        QVector3D pos2 = m2->getCurrentPosition();

        if (std::abs(pos1.x() - pos2.x()) > LOCATION_THRESHOLD || std::abs(pos1.y() - pos2.y()) > LOCATION_THRESHOLD)
            return false;
    }

    return true;
}
QJsonArray Pattern::toJson() const
{
    QJsonArray jsonArray;

    QVector3D previousEnd(0, 0, 0); // Initial start position (0, 0)

    for (int i = 0; i < m_movements.size() - 1; ++i) {

        Movement* movement = m_movements[i];
        QJsonObject movementJson;
        QJsonObject startJson;
        QJsonObject endJson;

        // Set the start position
        startJson["x"] = previousEnd.x();
        startJson["y"] = previousEnd.y();

        // Get the end position from the movement
        QVector3D endPos = movement->getCurrentPosition();
        endJson["x"] = endPos.x();
        endJson["y"] = endPos.y();

        // Set the direction and angle
        movementJson["start"] = startJson;
        movementJson["end"] = endJson;
        movementJson["direction"] = movement->getDirection();
        movementJson["angle"] = movement->getCurrentAngle();

        // Add the movement JSON to the array
        jsonArray.append(movementJson);

        // Update previousEnd for the next movement
        previousEnd = endPos;
    }
    qDebug() << jsonArray;

    return jsonArray;
}
