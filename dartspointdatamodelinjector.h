#ifndef DARTSPOINTDATAMODELINJECTOR_H
#define DARTSPOINTDATAMODELINJECTOR_H

#include "dartspointsinglecolumndatamodel.h"
#include "dartsdatamodelpointbuilder.h"
#include "convertpointtojson.h"

namespace DartsDataModelsContext {
    class DartsPointDataModelInjector : public DartsPointSingleColumnDataModel
    {
    public:
        DartsPointDataModelInjector()
        {
            _pointModelBuilderService = new dartsdatamodelpointbuilder;
            _convertPointToJsonService = new ConvertPointToJson;
        }
    };
}

#endif // DARTSPOINTDATAMODELINJECTOR_H
