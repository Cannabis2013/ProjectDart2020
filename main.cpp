#include "testconfiguration.h"
#ifndef TEST_MODE
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <qqmlcontext.h>

#include "defaultpointmulticolumnmodel.h"
#include "dartsscoresinglecolumndatamodel.h"
#include "dartsscoremulticolumndatamodel.h"
#include "defaultpointsinglecolumnmodel.h"
#include "localdartapplication.h"

#include "connectservices.h"
void registerCustomTypes()
{
    qmlRegisterType<DartsScoreSingleColumnDataModel>("CustomItems",1,0,"DartsScoreSingleColumnDataModel");
    qmlRegisterType<DartsScoreMultiColumnDataModel>("CustomItems",1,0,"DartsMultiAttemptDataModel");
    qmlRegisterType<DefaultPointMultiColumnModel>("CustomItems",1,0,"DartsPointMultiColumnDataModel");
    qmlRegisterType<DartsDataModelsContext::DefaultPointSingleColumnModel>("CustomItems",1,0,"DartsPointSingleColumnDataModel");
    qmlRegisterSingletonType(QUrl("qrc:/ThemeContext.qml"),"customDefinitions",1,0,"ThemeContext");
    qmlRegisterSingletonType(QUrl("qrc:/TournamentContext.qml"),"CustomValues",1,0,"TournamentContext");
    qmlRegisterSingletonType(QUrl("qrc:/DataModelContext.qml"),"CustomValues",1,0,"DataModelContext");
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    // Instantiate DartApplication
    auto _dart = LocalDartApplication::createAndSetupInstance();
    std::unique_ptr<ConnectServices> connectServices(new ConnectServices);
    connectServices->connectServices(_dart,_dart->routeServices(),_dart->connectServices());
    // Register custom types/singletons
    registerCustomTypes();
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
