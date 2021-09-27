#include "testconfiguration.h"
#ifndef TEST_MODE
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <qqmlcontext.h>
#include <registerqmldartstabletypes.h>
#include "applicationbuilder.h"
#include "registerqmlsingletons.h"
#include "registerqmltableutils.h"
#include "setupqmlcontext.h"
#include "registercustomtypes.h"

int main(int argc, char *argv[])
{
    // Configure for devices that supports hidp resolutions
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // Declare types that deals with main event loop and qml context
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    // Create and setup dart application backend
    ApplicationBuilder appCreator(engine,app);
    // Register custom types
    RegisterCustomTypes::registerTypes();
    // Setup QML UI interface
    SetupQMLContext::setup(engine,app,QStringLiteral("qrc:/qml/main.qml"));
    // Start main event loop
    return app.exec();
}
#endif