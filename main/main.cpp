#include "testconfiguration.h"
#ifndef TEST_MODE
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "QmlContext/qmlpropertiesbuilder.h"
#include <QtQuick/QQuickView>
#include <qqmlcontext.h>
#include "registerqmldartstabletypes.h"
#include "registerqmlsingletons.h"
#include "registerqmltableutils.h"
#include "setupqmlcontext.h"
#include "registerqmltypes.h"
int main(int argc, char *argv[])
{
    // Configure for devices that supports hidp resolutions
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // Register custom types
    RegisterQMLTypes::registerTypes();
    QmlPropertiesBuilder builder;
    // Setup main event loop and qml context
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperties(builder.contextProperties());
    // Setup QML UI interface
    SetupQMLContext::setup(engine,app,QStringLiteral("qrc:/qml/main.qml"));
    // Start main event loop
    return app.exec();
}
#endif
