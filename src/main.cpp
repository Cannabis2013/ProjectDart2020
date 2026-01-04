#include <QGuiApplication>
#include <QtSystemDetection>
#include "qqmlcontext.h"
#include "src/FileIO/filehtml.h"
#include "src/Finishes/dartsfinishes.h"
#include "src/dartsservices.h"
#include "src/init/dartsinitializer.h"
#include "src/input/controllers/dartsinputcontroller.h"
#include "src/players/controller/playerreport.h"
#include "src/scores/controller/remainingscontroller.h"
#include "src/statistics/controllers/dartsstatistics.h"
#include "src/turns/controller/dartsturncontroller.h"
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
    auto playersReport = new PlayerReport(services);
    auto dartsFinishes = new DartsFinishes();
    auto pageText = new FileHtml();

    engine->rootContext()->setContextProperty("fileHtml", pageText);
    engine->rootContext()->setContextProperty("dartsFinishes", dartsFinishes);
    engine->rootContext()->setContextProperty("winnerInfo", winnerInfo);
    engine->rootContext()->setContextProperty("dartsInitializer", initializer);
    engine->rootContext()->setContextProperty("dartsInputs", inputController);
    engine->rootContext()->setContextProperty("dartsStats", statsReport);
    engine->rootContext()->setContextProperty("dartsScores", scoresReport);
    engine->rootContext()->setContextProperty("dartsPlayers", playersReport);
    engine->rootContext()->setContextProperty("dartsTurns", turnController);

    return app.exec();
}
