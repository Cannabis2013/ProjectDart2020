#include "src/DartsController/controller/dartscontrollerbuilder.h"
#include "src/FileIO/filereader.h"
#include "src/Sounds/soundcontroller.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <qqmlcontext.h>

QQmlApplicationEngine* createEngine(const QGuiApplication& app)
{
        QQmlApplicationEngine* engine = new QQmlApplicationEngine();
        QUrl url("qrc:/qml/main.qml");
        QObject::connect(
            engine, &QQmlApplicationEngine::objectCreated,
            &app, [url](QObject* obj, const QUrl& objUrl) {
                    if (!obj && url == objUrl)
                            QCoreApplication::exit(-1);
            },
            Qt::QueuedConnection);
        engine->load(url);
        return engine;
}

void registerServices(QQmlApplicationEngine* const engine)
{
        auto soundController = new SoundController();
        auto dartsController = DartsControllerBuilder().build();
        auto fileReader = new FileReader();
        engine->rootContext()->setContextProperty("dartsController", dartsController);
        engine->rootContext()->setContextProperty("soundController", soundController);
        engine->rootContext()->setContextProperty("fileReader", fileReader);
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
        // Setup main event loop and qml context
        QGuiApplication app(argc, argv);
        // Create QML engine
        auto engine = createEngine(app);
        // Register custom services
        registerServices(engine);
        // Start main event loop
        return app.exec();
}
