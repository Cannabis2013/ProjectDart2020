#ifndef DSSCTABLEMODEL_H
#define DSSCTABLEMODEL_H

#include "dartstablemodel.h"
#include "dartstabledimensions.h"
#include "dartstablecellcontext.h"
#include "dartstablefillservice.h"
#include "dartstablecreatecolumnindices.h"
#include "dartstablecreaterowindices.h"
#include "dartspmcdatacontext.h"
#include "dartstablecreatecolumns.h"
#include "createjsonfromdp.h"
#include "createqmlvariants.h"
#include "dartsdatacontextitemutility.h"
#include "dartspscIndexBuilder.h"
#include "dartspmcsectionutility.h"
#include <dartstablesectionmanipulator.h>
// DartsSingleColumnTableModel
class DSSCTableModel : public DartsTableModel
{
   public:
    DSSCTableModel()
    {
        setTableSections(new DartsTableDimensions);
        setTableCellContext(new DartsTableCellContext);
        setCreateRows(new DartsTableCreateRows);
        setCreateColumns(new DartsTableCreateColumns);
        setCreateColumnIndiceValues(new DartsTableCreateColumnIndices);
        setCreateRowsIndices(new DartsTableCreateRowIndices);
        setDataContext(new DartsPMCDataContext);
        setTableItemBuilder(new CreateJsonFromDP);
        setQMLVariantsContext(new CreateQMLVariants);
        setGetDataFromDataContext(new DartsDataContextItemUtility);
        setcolumnIndexBuilder(new DartsPSCIndexBuilder);
        setSectionUtitity(new DartsPMCSectionUtility);
        setSectionManipulator(new DartsTableSectionManipulator); // Practically useless as there is no need to remove sections
    }
};

#endif // DSSCTABLEMODEL_H
