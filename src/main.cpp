#include <QGuiApplication>
#include <QtSystemDetection>
#include "qqmlcontext.h"
#include "src/FileIO/filehtml.h"
#include "src/Finishes/dartsfinishes.h"
#include "src/dartsservices.h"
#include "src/init/dartsinitializer.h"
#include "src/input/dartsinputcontroller.h"
#include "src/players/playercontroller.h"
#include "src/scores/remainingscontroller.h"
#include "src/servicecollection.h"
#include "src/statistics/dartsstatistics.h"
#include "src/turns/dartsturncontroller.h"
#include "src/winner/winnerinfo.h"
#include <qqmlapplicationengine.h>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine* engine = new QQmlApplicationEngine();
    QUrl url("qrc:/qml/main.qml");
    QObject::connect(
      engine,
      &QQmlApplicationEngine::objectCreated,
      &app,
      [url](QObject* obj, const QUrl& objUrl) {
          if (!obj && url == objUrl)
              QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
    engine->load(url);

    auto services = DartsServices().build();
    auto initializer = new DartsInitializer(services);
    auto winnerInfo = new WinnerInfo(services);
    auto inputController = new DartsInputController(services);
    auto statsReport = new DartsStatistics(services);
    auto scoresReport = new RemainingsController(services);
    auto turnController = new DartsTurnController(services);
    auto dartsFinishes = new DartsFinishes();
    auto pageText = new FileHtml();
    auto players = new PlayerController(services);

    engine->rootContext()->setContextProperty("fileHtml", pageText);
    engine->rootContext()->setContextProperty("dartsFinishes", dartsFinishes);
    engine->rootContext()->setContextProperty("winnerInfo", winnerInfo);
    engine->rootContext()->setContextProperty("dartsInitializer", initializer);
    engine->rootContext()->setContextProperty("dartsInputs", inputController);
    engine->rootContext()->setContextProperty("dartsStats", statsReport);
    engine->rootContext()->setContextProperty("dartsScores", scoresReport);
    engine->rootContext()->setContextProperty("dartsPlayers", players);
    engine->rootContext()->setContextProperty("dartsTurns", turnController);

    return app.exec();
}
