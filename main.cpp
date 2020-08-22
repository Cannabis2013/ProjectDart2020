#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

#include <qqmlcontext.h>
#include "applicationinterface.h"

#include "localplayerbuilder.h"

#include "localtournamentmodelscontext.h"
#include "localplayermodelscontext.h"

#include "scoredatamodel.h"

#include "gamebuilder.h"
#include "localplayermodelscontext.h"
#include "localtournamentmodelscontext.h"

#include "modelbuildercollection.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<ScoreDataModel>("CustomItems",1,0,"ScoreDataModel");

    auto tournamentModelsContext = new LocalTournamentModelsContext();
    tournamentModelsContext->setTournamentBuilder(new TournamentModelBuilder())
            ->setRoundBuilder(new RoundBuilder())->setSetBuilder(new SetBuilder())
            ->setPointBuilder(new PointBuilder());
    tournamentModelsContext->createDummyModels();

    auto playerModelsContext = new LocalPlayerModelsContext();
    playerModelsContext->setPlayerBuilder(new LocalPlayerBuilder());
    auto list = playerModelsContext->createDummyModels();

    tournamentModelsContext->assignToTournament(0,list);

    auto gameBuilder = new GameBuilder();

    auto _dart = new ApplicationInterface(tournamentModelsContext,
                                          playerModelsContext,
                                          gameBuilder);

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
