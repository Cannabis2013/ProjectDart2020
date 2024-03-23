#include "qmlsetup.h"
#include "src/FileIO/filehtml.h"
#include "src/Sounds/soundcontroller.h"
#include "src/dartsservices.h"
#include "src/init/serviceinitializer.h"
#include "src/input/controllers/dartsinputcontroller.h"
#include "src/players/controller/playerreport.h"
#include "src/scores/controller/dartsscorescontroller.h"
#include "src/statistics/controllers/dartsstatistics.h"
#include "src/turns/controller/dartsturncontroller.h"
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
        auto pageText = new FileHtml();
        _engine->rootContext()->setContextProperty("fileHtml", pageText);
        _engine->rootContext()->setContextProperty("dartsInitializer", initializer);
        _engine->rootContext()->setContextProperty("dartsInputs", inputController);
        _engine->rootContext()->setContextProperty("dartsStats", statsReport);
        _engine->rootContext()->setContextProperty("dartsScores", scoresReport);
        _engine->rootContext()->setContextProperty("dartsPlayers", playersReport);
        _engine->rootContext()->setContextProperty("dartsTurns", turnController);
        _engine->rootContext()->setContextProperty("soundController", soundController);
}
