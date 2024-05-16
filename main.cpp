#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "accelerometer.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Accelerometer>("com.example", 1, 0, "Accelerometer");

    QQmlApplicationEngine engine;
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
