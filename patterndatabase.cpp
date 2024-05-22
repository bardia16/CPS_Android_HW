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

void PatternDatabase::savePatternsToJson(const QString &fileName)
{
    QJsonArray jsonArray;

    for (Pattern *pattern : patterns) {
        jsonArray.append(pattern->toJson());
    }

    QJsonDocument jsonDoc(jsonArray);

    QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + fileName;
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open save file:" << filePath;
        return;
    }

    file.write(jsonDoc.toJson(QJsonDocument::Indented));
    file.close();
    qDebug() << "File saved to:" << filePath;
}

