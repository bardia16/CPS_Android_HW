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

    for (int i = 0; i < m_movements.size(); ++i) {
        const Movement* m1 = m_movements[i];
        const Movement* m2 = other->m_movements[i];

        if (std::abs(m1->getCurrentAngle() - m2->getCurrentAngle()) > 0.0)
            return false;

        QVector3D pos1 = m1->getCurrentPosition();
        QVector3D pos2 = m2->getCurrentPosition();

        if (std::abs(pos1.x() - pos2.x()) > LOCATION_THRESHOLD || std::abs(pos1.y() - pos2.y()) > LOCATION_THRESHOLD)
            return false;
    }

    return true;
}
