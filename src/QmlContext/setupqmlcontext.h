#ifndef SETUPQMLCONTEXT_H
#define SETUPQMLCONTEXT_H
#include "src/DartsController/dartscontroller.h"
#include <qurl.h>
#include <qobject.h>
#include <qqmlapplicationengine.h>
#include <qguiapplication.h>
#include <QQmlContext>

class SetupQMLContext
{
public:
    static void setup(QQmlApplicationEngine &engine, QGuiApplication &app, const QString &path)
    {
        const QUrl url(path);
        auto dartsController = new DartsController();
        engine.rootContext()->setContextProperty("dartsController",dartsController);
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
        engine.load(url);
    }
};
#endif // CREATEANDSETUPQMLCONTEXT_H
