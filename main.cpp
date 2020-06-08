#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>

#include "projectdart.h"

#include "customtablemodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<CustomTableModel>("CustomItems",1,0,"CustomTableModel");
    qmlRegisterType<ProjectDart>("ApplicationInterface",1,0,"ProjectDart");

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);


    return app.exec();
}
