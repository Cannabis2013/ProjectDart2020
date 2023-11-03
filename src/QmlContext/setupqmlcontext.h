#ifndef SETUPQMLCONTEXT_H
#define SETUPQMLCONTEXT_H

#include "src/DartsController/controller/dartscontrollerbuilder.h"
#include "src/Sounds/soundcontroller.h"
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
            auto soundController = new SoundController();
            auto dartsController = DartsControllerBuilder().build();
            engine.rootContext()->setContextProperty("dartsController", dartsController);
            engine.rootContext()->setContextProperty("soundController", soundController);
            QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated,
                &app, [url](QObject* obj, const QUrl& objUrl) {
                        if (!obj && url == objUrl)
                                QCoreApplication::exit(-1);
                },
                Qt::QueuedConnection);
            engine.load(url);
    }
};
#endif // CREATEANDSETUPQMLCONTEXT_H
