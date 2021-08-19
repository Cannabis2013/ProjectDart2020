#ifndef CREATEANDSETUPAPPLICATION_H
#define CREATEANDSETUPAPPLICATION_H

#include <QQmlApplicationEngine>
#include <qguiapplication.h>
#include <qqmlcontext.h>
#include "localdartapplication.h"
#include "connectservices.h"

class CreateAndSetupApplication
{
public:
    CreateAndSetupApplication(QQmlApplicationEngine &engine, QGuiApplication &app)
    {
        createApplications();
        connectMainApplication();
        createContextProperties();
        addToQMLRootContext(engine);
        connectInterface(engine,app);
    }
private:
    void createApplications()
    {
        _mainApp = LocalDartApplication::createAndSetupInstance();
    }
    void connectMainApplication()
    {
        std::unique_ptr<ConnectServices> connectServices(new ConnectServices);
        connectServices->connectServices(_mainApp,_mainApp->routeServices(),_mainApp->connectServices());
    }
    void connectInterface(QQmlApplicationEngine &engine, QGuiApplication &app)
    {
        QObject::connect(&engine,&QQmlApplicationEngine::quit,&app,[=]{
            delete _mainApp;
        },Qt::QueuedConnection);
    }
    void addToQMLRootContext(QQmlApplicationEngine &engine)
    {
        engine.rootContext()->setContextProperties(_QMLpropertyPairs);
    }
    void createContextProperties()
    {
        _QMLpropertyPairs << createProperty<AbstractApplicationInterface>("applicationInterface",_mainApp);
    }
    template<typename T>
    QQmlContext::PropertyPair createProperty(const QString &title, T *app)
    {
        QQmlContext::PropertyPair p;
        p.name = title;
        p.value = QVariant::fromValue<T*>(app);
        return p;
    }
    DartApplication *_mainApp;
    QVector<QQmlContext::PropertyPair> _QMLpropertyPairs;
};
#endif // SETUPAPPLICATION_H