#include "qmlsetup.h"
#include "src/DartsController/controller/dartscontrollerbuilder.h"
#include "src/FileIO/pagetexts.h"
#include "src/Sounds/soundcontroller.h"
#include "src/Utils/Fonts/fontmetrics.h"
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
        auto dartsController = DartsControllerBuilder().build();
        auto pageTexts = new PageTexts();
        auto fontMetrics = new FontMetrics("MS Sans Family");
        _engine->rootContext()->setContextProperty("fontMetrics", fontMetrics);
        _engine->rootContext()->setContextProperty("dartsController", dartsController);
        _engine->rootContext()->setContextProperty("soundController", soundController);
        _engine->rootContext()->setContextProperty("pageContents", pageTexts);
}
