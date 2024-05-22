#ifndef PATTERN_H
#define PATTERN_H

#include <QObject>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include "movement.h"

class Pattern : public QObject
{
    Q_OBJECT

public:
    explicit Pattern(const QList<Movement*> &movements, QObject *parent = nullptr);
    bool authenticate(Pattern *other) const;
    QJsonArray toJson() const;

private:
    QList<Movement*> m_movements;

    static constexpr double LOCATION_THRESHOLD = 0.5;
};

#endif // PATTERN_H
