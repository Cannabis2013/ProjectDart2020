#ifndef REGISTERQMLTYPES_H
#define REGISTERQMLTYPES_H

#include <dartsscoremulticolumndatamodel.h>
#include <dartsscoresinglecolumndatamodel.h>
#include <defaultpointmulticolumnmodel.h>
#include <defaultpointsinglecolumnmodel.h>
#include "verticalstringlabels.h"
#include "dartsroundindexbyattempt.h"

#include <QQmlApplicationEngine>

class RegisterQmlTypes
{
public:
    static void registerCustomTypes()
    {
        qmlRegisterType<DartsScoreSingleColumnDataModel>("CustomItems",1,0,"DartsScoreSingleColumnDataModel");
        qmlRegisterType<DartsScoreMultiColumnDataModel>("CustomItems",1,0,"DartsMultiAttemptDataModel");
        qmlRegisterType<DefaultPointMultiColumnModel>("CustomItems",1,0,"DartsPointMultiColumnDataModel");
        qmlRegisterType<DartsDataModelsContext::DefaultPointSingleColumnModel>("CustomItems",1,0,"DartsPointSingleColumnDataModel");
        qmlRegisterType<VerticalStringLabels>("CustomItems",1,0,"StringHeaderModel");
        qmlRegisterType<DartsRoundIndexByAttempt>("CustomItems",1,0,"RoundHeaderLabelByAttempt");
    }
    static void registerCustomSingletons()
    {
        qmlRegisterSingletonType(QUrl("qrc:/ThemeContext.qml"),"customDefinitions",1,0,"ThemeContext");
        qmlRegisterSingletonType(QUrl("qrc:/TournamentContext.qml"),"CustomValues",1,0,"TournamentContext");
        qmlRegisterSingletonType(QUrl("qrc:/DataModelContext.qml"),"CustomValues",1,0,"DataModelContext");
    }
private:
    template<typename T>
    static void registerCustomType(const char *typeName, const char *uri = "CustomItems")
    {
        qmlRegisterType<T>(uri,1,0,typeName);
    }
};

#endif // REGISTERQMLTYPES_H
