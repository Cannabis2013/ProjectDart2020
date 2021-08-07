#include "testconfiguration.h"
#ifndef TEST_MODE
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <localdartapplication.h>
#include <qqmlcontext.h>
#include "registerqmltypes.h"

#include "connectservices.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    // Instantiate DartApplication
    auto _dart = LocalDartApplication::createAndSetupInstance();
    std::unique_ptr<ConnectServices> connectServices(new ConnectServices);
    connectServices->connectServices(_dart,_dart->routeServices(),_dart->connectServices());
    // Register custom types/singletons
    RegisterQmlTypes::registerCustomTypes();
    RegisterQmlTypes::registerCustomSingletons();
    QQmlApplicationEngine engine;
    QQmlContext::PropertyPair p;
    p.name = "applicationInterface";
    p.value = QVariant::fromValue<AbstractApplicationInterface*>(_dart);
    engine.rootContext()->setContextProperties({p});
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    // Call DartApplication destructor
    QObject::connect(&engine,&QQmlApplicationEngine::quit,&app,[_dart]{
        delete _dart;
    },Qt::QueuedConnection);
    // Load main.qml
    engine.load(url);
    // Start main event loop
    return app.exec();
}
#endif
