#ifndef REGISTERQMLTYPES_H
#define REGISTERQMLTYPES_H
#include "registerqmltableutils.h"
#include <registerqmldartstabletypes.h>
#include <registerqmlsingletons.h>
class RegisterQMLTypes
{
public:
    static void registerTypes()
    {
        RegisterQMLDartsTableTypes::registerTableDataModels();
        RegisterQMLDartsTableTypes::registerTableHeaderModels();
        RegisterQmlSingleTons::registerCustomSingletons();
        RegisterQMLTableUtilities::registerTableSectionUtils();
    }
};

#endif // REGISTERQMLTYPES_H
