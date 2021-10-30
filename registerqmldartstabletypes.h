#ifndef REGISTERQMLDARTSTABLETYPES_H
#define REGISTERQMLDARTSTABLETYPES_H
#include <dssctablemodel.h>
#include <dpsctablemodel.h>
#include "dartsplayerdatamodel.h"
#include "dartsroundindexbyattempt.h"
#include <QQmlApplicationEngine>
class RegisterQMLDartsTableTypes
{
public:
    static void registerTableDataModels()
    {
        qmlRegisterType<DSSCTableModel>("CustomItems",1,0,"DSSCTableModel");
        qmlRegisterType<DPSCTableModel>("CustomItems",1,0,"DartsPSCTableModel");
    }
    static void registerTableHeaderModels()
    {
        qmlRegisterType<DartsPlayerDataModel>("CustomItems",1,0,"PlayerDataModel");
        qmlRegisterType<DartsRoundIndexByAttempt>("CustomItems",1,0,"RoundHeaderLabelByAttempt");
    }
};
#endif // REGISTERQMLTYPES_H
