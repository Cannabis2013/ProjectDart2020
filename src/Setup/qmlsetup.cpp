#include "qmlsetup.h"
#include "src/DartsController/dartsservices.h"
#include "src/DartsController/init/serviceinitializer.h"
#include "src/DartsController/input/controllers/dartsinputcontroller.h"
#include "src/DartsController/players/controller/playerreport.h"
#include "src/DartsController/scores/controller/dartsscorescontroller.h"
#include "src/DartsController/statistics/controllers/dartsstatistics.h"
#include "src/DartsController/turns/controller/dartsturncontroller.h"
#include "src/Sounds/soundcontroller.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

QmlSetup::QmlSetup(QGuiApplication* app)
    : _app(app)
{
}

void QmlSetup::setupApplication()
{
        createEngine();
        registerServices();
}

void QmlSetup::createEngine()
{
        QQmlApplicationEngine* engine = new QQmlApplicationEngine();
        QUrl url("qrc:/qml/main.qml");
        QObject::connect(
            engine, &QQmlApplicationEngine::objectCreated,
            _app, [url](QObject* obj, const QUrl& objUrl) {
                    if (!obj && url == objUrl)
                            QCoreApplication::exit(-1);
            },
            Qt::QueuedConnection);
        engine->load(url);
        _engine = engine;
}

void QmlSetup::registerServices()
{
        auto soundController = new SoundController();
        auto services = DartsServices().build();
        auto initializer = new ServiceInitializer(services);
        auto inputController = new DartsInputController(services);
        auto statsReport = new DartsStatistics(services);
        auto scoresReport = new DartsScoresController(services);
        auto turnController = new DartsTurnController(services);
        auto playersReport = new PlayerReport(services);
        _engine->rootContext()->setContextProperty("dartsInitializer", initializer);
        _engine->rootContext()->setContextProperty("dartsInputs", inputController);
        _engine->rootContext()->setContextProperty("dartsStats", statsReport);
        _engine->rootContext()->setContextProperty("dartsScores", scoresReport);
        _engine->rootContext()->setContextProperty("dartsPlayers", playersReport);
        _engine->rootContext()->setContextProperty("dartsTurns", turnController);
        _engine->rootContext()->setContextProperty("soundController", soundController);
}
