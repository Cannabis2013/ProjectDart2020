#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

#include <qqmlcontext.h>

#include "localdart.h"
#include "scoredatamodel.h"

#include "gamebuilder.h"
#include "localdatacontext.h"
#include "localplayermodelcontext.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<ScoreDataModel>("CustomItems",1,0,"ScoreDataModel");
    auto dataContext = new LocalDataContext("MHApps","Dart2020");
    auto gameBuilder = new GameBuilder();
    AbstractDartInterface *_dart = new LocalDart(dataContext,gameBuilder);

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
