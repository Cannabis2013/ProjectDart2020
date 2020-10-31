#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

#include <qqmlcontext.h>
#include "applicationinterface.h"
#include "playermodelbuilder.h"
#include "gamebuilder.h"
#include "localtournamentmodelscontext.h"
#include "localplayermodelscontext.h"
#include "firsttopostdatamodel.h"
#include "localtournamentmodeldb.h"
#include "localplayerdbcontext.h"
#include "tournamentmodelbuilder.h"
#include "playermodelbuilder.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<FirstToPostDataModel>("CustomItems",1,0,"ScoreDataModel");
    qmlRegisterSingletonType(QUrl("qrc:/ThemeContext.qml"),"customDefinitions",1,0,"ThemeContext");

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


    auto gameBuilder = new GameBuilder();

    auto _dart =
            ApplicationInterface::createInstance()->
            setTournamentsModelContext(tournamentModelsContext)->
            setPlayerModelsContext(playerModelsContext)->
            setControllerBuilder(gameBuilder)->
            useThreads()->
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
