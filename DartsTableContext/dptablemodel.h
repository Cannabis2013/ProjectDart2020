#ifndef DPTABLEMODEL_H
#define DPTABLEMODEL_H
#include "dartstablemodel.h"
#include "dartstabledimensions.h"
#include "dartstablecellcontext.h"
#include "DartsTableContext/TableCellsServices/dartsinitrowvalues.h"
#include "dartstablecreatecolumnindices.h"
#include "dartstablecreaterowindices.h"
#include "dartstabledatacontext.h"
#include "dartstablecreatecolumns.h"
#include "createqmlvariants.h"
#include "dartsdatacontextitemutility.h"
#include "dartstablesectionutility.h"
#include <dartstablesectionmanipulator.h>
class DPTableModel : public DartsTableModel
{
public:
    DPTableModel()
    {
        setTableSections(new DartsTableDimensions);
        setTableCellContext(new DartsTableCellContext);
        setCreateRows(new DartsInitRowValues);
        setCreateColumns(new DartsTableCreateColumns);
        setCreateColumnIndiceValues(new DartsTableCreateColumnIndices);
        setCreateRowsIndices(new DartsTableCreateRowIndices);
        setDataContext(new DartsTableDataContext);
        setQMLVariantsContext(new CreateQMLVariants);
        setGetDataFromDataContext(new DartsDataContextItemUtility);
        setSectionUtitity(new DartsTableSectionUtility);
        setSectionManipulator(new DartsTableSectionManipulator);
    }
};
#endif // DPSCTABLEMODEL_H
