#ifndef DEFAULTPOINTMULTICOLUMNMODEL_H
#define DEFAULTPOINTMULTICOLUMNMODEL_H

#include "dartspointmulticolumndatamodel.h"
#include "dartstabledimensions.h"
#include "dartstablecellcontext.h"
#include "dartstablefillservice.h"
#include "dartstablecreatecolumnindices.h"
#include "dartstablecreaterowindices.h"
#include "dartstabledatacontext.h"
#include "dartstablecreatecolumns.h"
#include "dartstablecreatejson.h"

class DefaultPointMultiColumnModel : public DartsPointMultiColumnDataModel
{
public:
    DefaultPointMultiColumnModel()
    {
        setTableContext(new DartsTableDimensions);
        setTableCellContext(new DartsTableCellContext);
        setCreateRows(new DartsTableCreateRows);
        setCreateColumns(new DartsTableCreateColumns);
        setCreateColumnIndiceValues(new DartsTableCreateColumnIndices);
        setCreateRowsIndices(new DartsTableCreateRowIndices);
        setDataContext(new DartsTableDataContext);
        setCreateJsonFromModel(new DartsTableCreateJson);
    }
};

#endif // DEFAULTPOINTMULTICOLUMNMODEL_H
