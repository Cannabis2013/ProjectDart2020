#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

#include <qqmlcontext.h>
#include "dartapplication.h"
#include "playermodelbuilder.h"
#include "gamecontrollerbuilder.h"
#include "localtournamentmodelscontext.h"
#include "localplayermodelscontext.h"
#include "ftpdatamodel.h"
#include "localtournamentmodeldb.h"
#include "localplayerdbcontext.h"
#include "tournamentmodelbuilder.h"
#include "playermodelbuilder.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<FTPDataModel>("CustomItems",1,0,"FTPSingleDataModel");
    qmlRegisterSingletonType(QUrl("qrc:/ThemeContext.qml"),"customDefinitions",1,0,"ThemeContext");
    qmlRegisterSingletonType(QUrl("qrc:/TournamentContext.qml"),"CustomValues",1,0,"TournamentContext");
    qmlRegisterSingletonType(QUrl("qrc:/DataModelContext.qml"),"CustomValues",1,0,"DataModelContext");
    auto tournamentModelsContext =
            LocalTournamentModelsContext::createInstance()->
            setModelBuilder(new TournamentModelBuilder())->
            setModelDBContext(new LocalTournamentModelDB())->
            setup();

    auto playerModelsContext =
            LocalPlayerModelsContext::createInstance()->
            setPlayerBuilder(new PlayerModelBuilder())->
            setModelDBContext(new LocalPlayerDBContext)->
            setup();

    auto _dart =
            DartApplication::createInstance()->
            setTournamentsModelContext(tournamentModelsContext)->
            setPlayerModelsContext(playerModelsContext)->
            setControllerBuilder(new GameControllerBuilder())->
            /*useThreads()->*/
            setup();

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("applicationInterface",_dart);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QObject::connect(&engine,&QQmlApplicationEngine::quit,&app,[_dart]{
        delete _dart;
    },Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
