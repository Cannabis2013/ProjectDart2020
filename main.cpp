#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "QmlContext/qmlpropertiesbuilder.h"
#include <QtQuick/QQuickView>
#include <qqmlcontext.h>
#include "QmlContext/registerqmldartstabletypes.h"
#include "QmlContext/registerqmlsingletons.h"
#include "QmlContext/registerqmltableutils.h"
#include "QmlContext/setupqmlcontext.h"
#include "QmlContext/registerqmltypes.h"
int main(int argc, char *argv[])
{
    // Configure for devices that supports hidp resolutions
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // Setup main event loop and qml context
    QGuiApplication app(argc, argv);
    // Register custom typQStringLiterales
    RegisterQMLTypes::registerTypes();
    // Build and add context properties
    QmlPropertiesBuilder builder;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperties(builder.contextProperties());
    // Setup QML UI interface
    SetupQMLContext::setup(engine,app,QStringLiteral("qrc:/qml/main.qml"));
    // Start main event loop
    return app.exec();
}
