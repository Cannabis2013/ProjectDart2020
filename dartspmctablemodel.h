#ifndef DARTSPMCTABLEMODEL_H
#define DARTSPMCTABLEMODEL_H

#include "dartstablemodel.h"
#include "dartstabledimensions.h"
#include "dartstablecellcontext.h"
#include "dartstablefillservice.h"
#include "dartstablecreatecolumnindices.h"
#include "dartstablecreaterowindices.h"
#include "dartspmcdatacontext.h"
#include "dartstablecreatecolumns.h"
#include "createqmljson.h"
#include "createqmlvariants.h"
#include "dartsdatacontextitemutility.h"
#include "dartspmccolumnindexbuilder.h"
#include "dartspmcsectionutility.h"

class DartsPMCTableModel : public DartsTableModel
{
public:
    DartsPMCTableModel()
    {
        setTableContext(new DartsTableDimensions);
        setTableCellContext(new DartsTableCellContext);
        setCreateRows(new DartsTableCreateRows);
        setCreateColumns(new DartsTableCreateColumns);
        setCreateColumnIndiceValues(new DartsTableCreateColumnIndices);
        setCreateRowsIndices(new DartsTableCreateRowIndices);
        setDataContext(new DartsPMCDataContext);
        setTableItemBuilder(new CreateQMLJson);
        setQMLVariantsContext(new CreateQMLVariants);
        setGetDataFromDataContext(new DartsDataContextItemUtility);
        setcolumnIndexBuilder(new DartsPMCColumnIndexBuilder);
        setSectionUtitity(new DartsPMCSectionUtility);
    }
};

#endif // DEFAULTPOINTMULTICOLUMNMODEL_H
