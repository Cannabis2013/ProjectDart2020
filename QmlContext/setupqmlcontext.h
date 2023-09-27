#ifndef SETUPQMLCONTEXT_H
#define SETUPQMLCONTEXT_H
#include <qurl.h>
#include <qobject.h>
#include <qqmlapplicationengine.h>
#include <qguiapplication.h>

class SetupQMLContext
{
public:
    static void setup(QQmlApplicationEngine &engine, QGuiApplication &app, const QString &path)
    {
        const QUrl url(path);
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
        engine.load(url);
    }
};
#endif // CREATEANDSETUPQMLCONTEXT_H
