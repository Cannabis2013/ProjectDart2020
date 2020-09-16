#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

#include <qqmlcontext.h>
#include "applicationinterface.h"
#include "localplayerbuilder.h"
#include "gamebuilder.h"
#include "localtournamentmodelscontext.h"
#include "localplayermodelscontext.h"
#include "scoredatamodel.h"
#include "localtournamentmodeldb.h"
#include "localplayerdbcontext.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<ScoreDataModel>("CustomItems",1,0,"ScoreDataModel");

    auto tournamentModelsContext =
            LocalTournamentModelsContext::createInstance()->
            setTournamentModelBuilder(new TournamentModelBuilder)->
            setRoundModelBuilder(new RoundBuilder)->
            setSetModelBuilder(new SetBuilder())->
            setScoreModelBuilder(new ScoreModelBuilder())->
            setModelDBContext(new LocalTournamentModelDB())->
            setup();

    auto playerModelsContext =
            LocalPlayerModelsContext::createInstance()->
            setPlayerBuilder(new LocalPlayerBuilder)->
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
