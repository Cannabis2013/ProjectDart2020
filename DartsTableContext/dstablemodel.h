#ifndef DSTABLEMODEL_H
#define DSTABLEMODEL_H
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
class DSTableModel : public DartsTableModel
{
   public:
    DSTableModel()
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
        setSectionManipulator(new DartsTableSectionManipulator); // Practically useless as there is no need to remove sections
    }
};
#endif // DSTABLEMODEL_H
