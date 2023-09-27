#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include "QmlContext/qmlpropertiesbuilder.h"
#include "QmlContext/registerqmltypes.h"
#include "QmlContext/setupqmlcontext.h"
#include <qqmlcontext.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
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
