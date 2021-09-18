#ifndef REGISTERCUSTOMTYPES_H
#define REGISTERCUSTOMTYPES_H

#include "registerqmltableutils.h"
#include <registerqmldartstabletypes.h>
#include <registerqmlsingletons.h>

class RegisterCustomTypes
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

#endif // REGISTERCUSTOMTYPES_H
