#ifndef REGISTERQMLSINGLETONS_H
#define REGISTERQMLSINGLETONS_H

#include <qurl.h>
#include <qqml.h>

class RegisterQmlSingleTons
{
public:
    static void registerCustomSingletons()
    {
        qmlRegisterSingletonType(QUrl("qrc:/ThemeContext.qml"),"customDefinitions",1,0,"ThemeContext");
        qmlRegisterSingletonType(QUrl("qrc:/TournamentContext.qml"),"CustomValues",1,0,"TournamentContext");
        qmlRegisterSingletonType(QUrl("qrc:/DataModelContext.qml"),"CustomValues",1,0,"DataModelContext");
    }
};

#endif // REGISTERQMLSINGLETONS_H
