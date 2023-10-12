#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include "QmlContext/setupqmlcontext.h"
#include <qqmlcontext.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    // Setup main event loop and qml context
    QGuiApplication app(argc, argv);
    // Build and add context properties
    QQmlApplicationEngine engine;
    qputenv("QML_XHR_ALLOW_FILE_READ", QString("1").toUtf8());
    // Setup QML UI interface
    SetupQMLContext::setup(engine,app,QStringLiteral("qrc:/qml/main.qml"));
    // Start main event loop
    return app.exec();
}
