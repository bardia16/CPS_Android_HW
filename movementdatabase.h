#ifndef MOVEMENTDATABASE_H
#define MOVEMENTDATABASE_H

#include <QObject>
#include <QList>
#include "movement.h"

class MovementDatabase : public QObject
{
    Q_OBJECT

public:
    explicit MovementDatabase(QObject *parent = nullptr);

    Q_INVOKABLE void handleNewAcceleration(double x, double y, double velocityX, double velocityY, double xBias, double yBias);

    QList<Movement *> movements() const;

signals:
    void movementsUpdated(qreal x_pos, qreal y_pos);

private:
    Movement *currentMovement;
    QList<Movement *> m_movements;
    void createNewMovement();
};

#endif // MOVEMENTDATABASE_H
