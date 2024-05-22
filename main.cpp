#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "accelerometer.h"
#include "gyroscope.h"
#include "movementdatabase.h"
#include "patterndatabase.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Accelerometer>("com.example", 1, 0, "Accelerometer");
    qmlRegisterType<Gyroscope>("com.example", 1, 0, "Gyroscope");
    qmlRegisterType<MovementDatabase>("com.example", 1, 0, "MovementDatabase");
    qmlRegisterType<PatternDatabase>("com.example", 1, 0, "PatternDatabase");

    QQmlApplicationEngine engine;

    MovementDatabase movementDatabase;
    engine.rootContext()->setContextProperty("movementDatabase", &movementDatabase);

    const QUrl url(u"qrc:/QtQuickProject/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
