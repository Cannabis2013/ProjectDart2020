#ifndef REGISTERQMLSINGLETONS_H
#define REGISTERQMLSINGLETONS_H

#include <qurl.h>
#include <qqml.h>

class RegisterQmlSingleTons
{
public:
    static void registerCustomSingletons()
    {
        qmlRegisterSingletonType(QUrl("qrc:/qml/TournamentContext.qml"),"CustomValues",1,0,"TournamentContext");
        qmlRegisterSingletonType(QUrl("qrc:/qml/DataModelContext.qml"),"CustomValues",1,0,"DataModelContext");
    }
};

#endif // REGISTERQMLSINGLETONS_H
