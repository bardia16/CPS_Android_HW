#ifndef MOVEMENTDATABASE_H
#define MOVEMENTDATABASE_H

#include <QObject>
#include <QList>
#include "movement.h"
#include "pattern.h"

class MovementDatabase : public QObject
{
    Q_OBJECT

public:
    explicit MovementDatabase(QObject *parent = nullptr);

    Q_INVOKABLE void handleNewAcceleration(double x, double y, double velocityX, double velocityY, double xBias, double yBias);
    Q_INVOKABLE void handleNewAngle(double alpha);
    Q_INVOKABLE void reset();


    QString getDirection();

public slots:
    void createNewPattern(bool isAttempt);

signals:
    void movementsUpdated(qreal x_pos, qreal y_pos, qreal angle, QString direction);
    void angleUpdated(double alpha);
    void newPattern(Pattern *pattern);
    void newAttempt(Pattern *pattern);

private:
    Movement *currentMovement;
    QList<Movement *> m_movements;
    void createNewMovement();
};

#endif // MOVEMENTDATABASE_H
