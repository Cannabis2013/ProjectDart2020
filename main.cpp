#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

#include <qqmlcontext.h>
#include "dartapplication.h"
#include "playermodelbuilder.h"
#include "gamecontrollerbuilder.h"
#include "localtournamentmodelscontext.h"
#include "localplayermodelscontext.h"
#include "remotemodelscontext.h"
#include "localmodelscontext.h"
#include "ftpdatamodel.h"
#include "tournamentbuilder.h"
#include "playermodelbuilder.h"
#include "sftpdatamodel.h"


DartApplication* createDartApplication()
{
    auto _dart =
            DartApplication::createInstance()->
            setModelsContextInterface(LocalModelsContext::createInstance())->
            setControllerBuilder(new GameControllerBuilder())->
            /*useThreads()->*/
            setup();
    return _dart;
}

void registerCustomTypes()
{
    qmlRegisterType<SFTPDataModel>("CustomItems",1,0,"SFTPDataModel");
    qmlRegisterType<FTPDataModel>("CustomItems",1,0,"FTPDataModel");
    qmlRegisterSingletonType(QUrl("qrc:/ThemeContext.qml"),"customDefinitions",1,0,"ThemeContext");
    qmlRegisterSingletonType(QUrl("qrc:/TournamentContext.qml"),"CustomValues",1,0,"TournamentContext");
    qmlRegisterSingletonType(QUrl("qrc:/DataModelContext.qml"),"CustomValues",1,0,"DataModelContext");
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    /*
     * Configue DartApplication
     * Instantiate DartApplication
     */
    auto _dart = createDartApplication();
#ifndef TEST_MODE
    /*
     * Register custom types/singletons
     */
    registerCustomTypes();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationInterface",_dart);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    /*
     * Call DartApplication destructor
     */
    QObject::connect(&engine,&QQmlApplicationEngine::quit,&app,[_dart]{
        delete _dart;
    },Qt::QueuedConnection);
    /*
     * Load main.qml
     */
    engine.load(url);
    /*
     * Start main event loop
     */
#endif
#ifdef TEST_MODE
    // Insert test methods here

    _dart->modelsContextInterface()->handleRequestTournaments();

#endif
    return app.exec();
}
