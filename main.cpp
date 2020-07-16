#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

#include <qqmlcontext.h>

#include "localdart.h"
#include "scoredatamodel.h"

#include "gamebuilder.h"
#include "localdatacontext.h"
#include "localplayercontext.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<ScoreDataModel>("CustomItems",1,0,"ScoreDataModel");

    AbstractDartInterface *_dart = new LocalDart();

    _dart->setDataContext(new LocalDataContext("MHapps","Dart2020"));
    _dart->setPlayerContext(new LocalPlayerContext);
    _dart->setControllerBuilder(new GameBuilder());
    _dart->createInitialModels();

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("localDart",_dart);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);


    return app.exec();
}
