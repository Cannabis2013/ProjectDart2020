#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

#include <qqmlcontext.h>
#include "applicationinterface.h"

#include "scoredatamodel.h"

#include "gamebuilder.h"
#include "localdatacontext.h"
#include "localplayermodelcontext.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    /*
    QCoreApplication::setOrganizationName("MHApps");
    QCoreApplication::setApplicationName("Dart2020");
    QCoreApplication::setOrganizationDomain("MHApps");
    */
    QGuiApplication app(argc, argv);

    qmlRegisterType<ScoreDataModel>("CustomItems",1,0,"ScoreDataModel");
    auto dataContext = new LocalDataContext("MHApps","Dart2020");
    auto gameBuilder = new GameBuilder();

    auto _dart = new ApplicationInterface(dataContext,gameBuilder);

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
