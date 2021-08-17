#ifndef REGISTERQMLDARTSTABLETYPES_H
#define REGISTERQMLDARTSTABLETYPES_H

#include <dartssmctablemodel.h>
#include <dartsscoresinglecolumndatamodel.h>
#include <dartspmctablemodel.h>
#include <defaultpointsinglecolumnmodel.h>
#include "verticalstringlabels.h"
#include "dartsroundindexbyattempt.h"
#include <QQmlApplicationEngine>

class RegisterQMLDartsTableTypes
{
public:
    static void registerTableDataModels()
    {
        qmlRegisterType<DartsScoreSingleColumnDataModel>("CustomItems",1,0,"DartsScoreSingleColumnDataModel");
        qmlRegisterType<DartsSMCTableModel>("CustomItems",1,0,"DartsMultiAttemptDataModel");
        qmlRegisterType<DartsPMCTableModel>("CustomItems",1,0,"DartsPMCTableModel");
        qmlRegisterType<DefaultPointSingleColumnModel>("CustomItems",1,0,"DartsPointSingleColumnDataModel");
    }
    static void registerTableHeaderModels()
    {
        qmlRegisterType<VerticalStringLabels>("CustomItems",1,0,"StringHeaderModel");
        qmlRegisterType<DartsRoundIndexByAttempt>("CustomItems",1,0,"RoundHeaderLabelByAttempt");
    }
};

#endif // REGISTERQMLTYPES_H
