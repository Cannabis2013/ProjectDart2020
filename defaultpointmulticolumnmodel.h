#ifndef DEFAULTPOINTMULTICOLUMNMODEL_H
#define DEFAULTPOINTMULTICOLUMNMODEL_H

#include "dartspointmulticolumndatamodel.h"

#include "dartspointcellstylistics.h"
#include "defaultdartscellcontext.h"
#include "defaultdartstabledimensions.h"
#include "verticalstringifiedheadercontext.h"
#include "dartstableheaderstylistics.h"

class DefaultPointMultiColumnModel : public DartsPointMultiColumnDataModel
{
public:
    DefaultPointMultiColumnModel()
    {
        setFontContext(new DartsPointCellStylistics);
        setTableCellContext(new DefaultDartsCellContext);
        setTableContext(new DefaultDartsTableDimensions);
        setVerticalHeaderContext(new VerticalStringifiedHeaderContext);
    }
};

#endif // DEFAULTPOINTMULTICOLUMNMODEL_H
