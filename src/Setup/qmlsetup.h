#ifndef QMLSETUP_H
#define QMLSETUP_H

class QGuiApplication;
class QQmlApplicationEngine;

class QmlSetup {
public:
        QmlSetup(QGuiApplication* app);
        void setupApplication();

private:
        void createEngine();
        void registerServices();

        QQmlApplicationEngine* _engine;
        QGuiApplication* _app;
};

#endif // QMLSETUP_H
