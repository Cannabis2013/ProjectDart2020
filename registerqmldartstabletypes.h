#ifndef REGISTERQMLDARTSTABLETYPES_H
#define REGISTERQMLDARTSTABLETYPES_H

#include <dssctablemodel.h>
#include <dpmctablemodel.h>
#include <dpsctablemodel.h>
#include "verticalstringlabels.h"
#include "dartsroundindexbyattempt.h"
#include <QQmlApplicationEngine>

class RegisterQMLDartsTableTypes
{
public:
    static void registerTableDataModels()
    {
        qmlRegisterType<DSSCTableModel>("CustomItems",1,0,"DSSCTableModel");
        qmlRegisterType<DPMCTableModel>("CustomItems",1,0,"DPMCTableModel");
        qmlRegisterType<DPSCTableModel>("CustomItems",1,0,"DartsPSCTableModel");
    }
    static void registerTableHeaderModels()
    {
        qmlRegisterType<VerticalStringLabels>("CustomItems",1,0,"StringHeaderModel");
        qmlRegisterType<DartsRoundIndexByAttempt>("CustomItems",1,0,"RoundHeaderLabelByAttempt");
    }
};

#endif // REGISTERQMLTYPES_H
