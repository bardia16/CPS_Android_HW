#include "patterndatabase.h"
#include <QDebug>

PatternDatabase::PatternDatabase(QObject *parent)
    : QObject(parent)
{
}

void PatternDatabase::addPattern(Pattern *pattern)
{
    qDebug() << "Pattern created";
    patterns.append(pattern);
}

void PatternDatabase::authenticatePattern(Pattern *pattern)
{
    QString status = "failed";
    for (Pattern *storedPattern : patterns) {
        if (storedPattern->authenticate(pattern)) {
            status = "succeed";
        }
    }
    QString output = QStringLiteral("Authentication %1").arg(status);
    emit authenticationResult(output);
}
