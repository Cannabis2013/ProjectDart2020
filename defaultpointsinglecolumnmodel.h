#ifndef DEFAULTPOINTSINGLECOLUMNMODEL_H
#define DEFAULTPOINTSINGLECOLUMNMODEL_H

#include "dartspointsinglecolumndatamodel.h"
#include "dartsdatamodelpointbuilder.h"
#include "convertpointtojson.h"
#include <qqml.h>


namespace DartsDataModelsContext {
    class DefaultPointSingleColumnModel : public DartsPointSingleColumnDataModel
    {
    public:
        DefaultPointSingleColumnModel()
        {
            _pointModelBuilderService = new dartsdatamodelpointbuilder;
            _convertPointToJsonService = new ConvertPointToJson;
        }
    };
}

#endif // DARTSPOINTDATAMODELINJECTOR_H
