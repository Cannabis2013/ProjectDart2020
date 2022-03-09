#ifndef REGISTERQMLDARTSTABLETYPES_H
#define REGISTERQMLDARTSTABLETYPES_H
#include "DartsTableContext/dstablemodel.h"
#include "DartsTableContext/dptablemodel.h"
#include "DartsTableContext/QMLDartsDataModel/dartsplayerdatamodel.h"
#include <QQmlApplicationEngine>
class RegisterQMLDartsTableTypes
{
public:
    static void registerTableDataModels()
    {
        qmlRegisterType<DSTableModel>("CustomItems",1,0,"DSCTableModel");
        qmlRegisterType<DPTableModel>("CustomItems",1,0,"DPCTableModel");
    }
    static void registerTableHeaderModels()
    {
        qmlRegisterType<DartsPlayerDataModel>("CustomItems",1,0,"PlayerDataModel");
    }
};
#endif // REGISTERQMLTYPES_H
