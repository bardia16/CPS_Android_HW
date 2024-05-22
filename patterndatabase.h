#ifndef PATTERNDATABASE_H
#define PATTERNDATABASE_H

#include <QObject>
#include <QList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include "pattern.h"

class PatternDatabase : public QObject
{
    Q_OBJECT

public:
    explicit PatternDatabase(QObject *parent = nullptr);

public slots:
    void addPattern(Pattern *pattern);
    void authenticatePattern(Pattern *pattern);
    void savePatternsToJson(const QString &fileName);

signals:
    void authenticationResult(const QString &output);

private:
    QList<Pattern *> patterns;
};

#endif // PATTERNDATABASE_H
