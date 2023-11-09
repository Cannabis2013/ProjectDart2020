#include "src/Setup/qmlsetup.h"
#include <QGuiApplication>

int main(int argc, char* argv[])
{
        QGuiApplication app(argc, argv);
        QmlSetup qmlSetup(&app);
        qmlSetup.setupApplication();
        return app.exec();
}
