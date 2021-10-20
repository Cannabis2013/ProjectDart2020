#ifndef DPMCTABLEMODEL_H
#define DPMCTABLEMODEL_H

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
#include "dartspmccolumnindexbuilder.h"
#include "dartspmcsectionutility.h"
#include "dartstablesectionmanipulator.h"

class DPMCTableModel : public DartsTableModel
{
public:
    DPMCTableModel()
    {
        setTableSections(new DartsTableDimensions);
        setTableCellContext(new DartsTableCellContext);
        setCreateRows(new DartsTableCreateRows);
        setCreateColumns(new DartsTableCreateColumns);
        setCreateColumnIndiceValues(new DartsTableCreateColumnIndices);
        setCreateRowsIndices(new DartsTableCreateRowIndices);
        setDataContext(new DartsTableDataContext);
        setTableItemBuilder(new CreateJsonFromDP);
        setQMLVariantsContext(new CreateQMLVariants);
        setGetDataFromDataContext(new DartsDataContextItemUtility);
        setcolumnIndexBuilder(new DartsPMCColumnIndexBuilder);
        setSectionUtitity(new DartsPMCSectionUtility);
        setSectionManipulator(new DartsTableSectionManipulator);
    }
};

#endif // DEFAULTPOINTMULTICOLUMNMODEL_H
