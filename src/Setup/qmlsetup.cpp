#include "qmlsetup.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/FileIO/filehtml.h"
#include "src/Finishes/dartsfinishes.h"
#include "src/dartsservices.h"
#include "src/init/dartsinitializer.h"
#include "src/input/controllers/dartsinputcontroller.h"
#include "src/players/controller/playerreport.h"
#include "src/scores/controller/remainingscontroller.h"
#include "src/statistics/controllers/dartsstatistics.h"
#include "src/turns/controller/dartsturncontroller.h"

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
        auto services = DartsServices().build();
        auto initializer = new DartsInitializer(services);
        auto inputController = new DartsInputController(services);
        auto statsReport = new DartsStatistics(services);
        auto scoresReport = new RemainingsController(services);
        auto turnController = new DartsTurnController(services);
        auto playersReport = new PlayerReport(services);
        auto dartsFinishes = new DartsFinishes();
        auto pageText = new FileHtml();
        _engine->rootContext()->setContextProperty("fileHtml", pageText);
        _engine->rootContext()->setContextProperty("dartsFinishes", dartsFinishes);
        _engine->rootContext()->setContextProperty("dartsInitializer", initializer);
        _engine->rootContext()->setContextProperty("dartsInputs", inputController);
        _engine->rootContext()->setContextProperty("dartsStats", statsReport);
        _engine->rootContext()->setContextProperty("dartsScores", scoresReport);
        _engine->rootContext()->setContextProperty("dartsPlayers", playersReport);
        _engine->rootContext()->setContextProperty("dartsTurns", turnController);
}
