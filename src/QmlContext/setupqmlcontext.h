#ifndef SETUPQMLCONTEXT_H
#define SETUPQMLCONTEXT_H
#include "src/Config/dartsconfig.h"
#include "src/DartsController/dartscontroller.h"
#include <QQmlContext>
#include <qguiapplication.h>
#include <qobject.h>
#include <qqmlapplicationengine.h>
#include <qurl.h>

class SetupQMLContext
{
public:
    static void setup(QQmlApplicationEngine &engine, QGuiApplication &app, const QString &path)
    {
        const QUrl url(path);
        auto dartsController = new DartsController();
        auto dartsConfig = new DartsConfig();
        engine.rootContext()->setContextProperty("dartsController",dartsController);
        engine.rootContext()->setContextProperty("dartsConfig", dartsConfig);
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
        engine.load(url);
    }
};
#endif // CREATEANDSETUPQMLCONTEXT_H
