#include "testconfiguration.h"
#ifndef TEST_MODE
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

#include <qqmlcontext.h>
#include "dartapplication.h"
#include "dartscontrollerbuilder.h"
#include "remotemodelscontext.h"
#include "dartsmultipointdatamodel.h"
#include "sftpdatamodel.h"
#include "dartsmultiscoredatamodel.h"
#include "assembledartstournamentmodelfromjson.h"
#include "connectdartssingleattemptpointcontroller.h"
#include "connectdartsscorecontroller.h"
#include "defaultmodelsservicebuilder.h"
#include "dartsmodelservicebuilder.h"
#include "playermodelsservicebuilder.h"
#include "connectdefaultmodelscontextinterface.h"
#include "connectcontrollerbuilder.h"

DartApplication* createDartApplication()
{
    auto dartsControllerBuilder = DartsControllerBuilder::createInstance()
            ->setConnectDartsSingleAttemptPointController(new ConnectDartsSingleAttemptPointController)
            ->setConnectDartsScoreController(new ConnectDartsScoreController);
    auto modelsServiceBuilder = DefaultModelsServiceBuilder::createInstance()
            ->setModelsTournamentServiceBuilder(new DartsModelServiceBuilder)
            ->setPlayerServiceBuilder(new PlayerModelsServiceBuilder);
    auto _dart =
            DartApplication::createInstance()->
            setModelsServiceBuilder(modelsServiceBuilder)->
            setControllerBuilder(dartsControllerBuilder)->
            setConnectModelsServiceInterface(new ConnectDefaultModelsContextInterface)
            ->setConnectControllerBuilder(new ConnectControllerBuilder)
            /*useThreads()->*/
            ->setup();
    return _dart;
}

void registerCustomTypes()
{
    qmlRegisterType<SFtpDataModel>("CustomItems",1,0,"SFtpDataModel");
    qmlRegisterType<DartsMultiPointDataModel>("CustomItems",1,0,"DartsPointDatamodel");
    qmlRegisterType<DartsMultiScoreDataModel>("CustomItems",1,0,"DartsMultiScoreDataModel");
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
    return app.exec();
}
#endif
