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

void registerTypes()
{
    RegisterQMLDartsTableTypes::registerTableDataModels();
    RegisterQMLDartsTableTypes::registerTableHeaderModels();
    RegisterQmlSingleTons::registerCustomSingletons();
    RegisterQMLTableUtilities::registerTableSectionUtils();
}

void setupQMLContext(QQmlApplicationEngine &engine, QGuiApplication &app)
{
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    // Load main.qml
    engine.load(url);
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    // Create and setup dart application backend
    ApplicationBuilder appCreator(engine,app);
    // Register custom types
    registerTypes();
    // Setup QML UI interface
    setupQMLContext(engine,app);
    // Start main event loop
    return app.exec();
}
#endif
