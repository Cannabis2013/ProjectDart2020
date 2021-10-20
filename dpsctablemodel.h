#ifndef DPSCTABLEMODEL_H
#define DPSCTABLEMODEL_H

#include "dartstablemodel.h"
#include "dartstabledimensions.h"
#include "dartstablecellcontext.h"
#include "dartstablefillservice.h"
#include "dartstablecreatecolumnindices.h"
#include "dartstablecreaterowindices.h"
#include "dartstabledatacontext.h"
#include "dartstablecreatecolumns.h"
#include "createjsonfromdp.h"
#include "createqmlvariants.h"
#include "dartsdatacontextitemutility.h"
#include "dartspscIndexBuilder.h"
#include "dartspmcsectionutility.h"
#include <createscorevaluefromdi.h>
#include <dartstablesectionmanipulator.h>

class DPSCTableModel : public DartsTableModel
{
public:
    DPSCTableModel()
    {
        setTableSections(new DartsTableDimensions);
        setTableCellContext(new DartsTableCellContext);
        setCreateRows(new DartsTableCreateRows);
        setCreateColumns(new DartsTableCreateColumns);
        setCreateColumnIndiceValues(new DartsTableCreateColumnIndices);
        setCreateRowsIndices(new DartsTableCreateRowIndices);
        setDataContext(new DartsTableDataContext);
        setTableItemBuilder(new CreateScoreValueFromDI);
        setQMLVariantsContext(new CreateQMLVariants);
        setGetDataFromDataContext(new DartsDataContextItemUtility);
        setcolumnIndexBuilder(new DartsPSCIndexBuilder);
        setSectionUtitity(new DartsPMCSectionUtility);
        setSectionManipulator(new DartsTableSectionManipulator); // Practically useless as there is no need to remove sections
    }
};
#endif // DPSCTABLEMODEL_H
