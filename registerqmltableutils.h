#ifndef REGISTERQMLTABLEUTILS_H
#define REGISTERQMLTABLEUTILS_H

#include "mhtablesectionmetrics.h"
#include "mhtablecolumnwidth.h"
#include "mhtablerowheight.h"
#include "qqml.h"

class RegisterQMLTableUtilities
{
public:
    static void registerTableSectionUtils()
    {
        qmlRegisterType<MHTableSectionMetrics>("DartsTableUtils",1,0,"TableSectionMetrics");
        qmlRegisterType<MHTableColumnWidth>("DartsTableUtils",1,0,"DartsTableWidths");
        qmlRegisterType<MHTablerowHeight>("DartsTableUtils",1,0,"DartsTableHeights");
    }
};

#endif // REGISTERQMLTABLEUTILS_H
