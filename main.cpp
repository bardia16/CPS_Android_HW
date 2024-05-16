#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "accelerometer.h"
#include "movementdatabase.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Accelerometer>("com.example", 1, 0, "Accelerometer");
    qmlRegisterType<MovementDatabase>("com.example", 1, 0, "MovementDatabase"); // Register MovementDatabase

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
