#ifndef DARTSPMCTABLEMODEL_H
#define DARTSPMCTABLEMODEL_H

#include "dartsmctablemodel.h"
#include "dartstabledimensions.h"
#include "dartstablecellcontext.h"
#include "dartstablefillservice.h"
#include "dartstablecreatecolumnindices.h"
#include "dartstablecreaterowindices.h"
#include "dartstabledatacontext.h"
#include "dartstablecreatecolumns.h"
#include "createqmljson.h"
#include "createqmlvariants.h"

class DartsPMCTableModel : public DartsMCTableModel
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
        setDataContext(new DartsTableDataContext);
        setQMLJsonContext(new CreateQMLJson);
        setQMLVariantsContext(new CreateQMLVariants);
    }
};

#endif // DEFAULTPOINTMULTICOLUMNMODEL_H
