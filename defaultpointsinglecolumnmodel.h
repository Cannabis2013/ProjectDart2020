#ifndef DEFAULTPOINTSINGLECOLUMNMODEL_H
#define DEFAULTPOINTSINGLECOLUMNMODEL_H

#include "dartspointsinglecolumndatamodel.h"
#include "dartsdatamodelpointbuilder.h"
#include "convertpointtojson.h"
#include <qqml.h>


class DefaultPointSingleColumnModel : public DartsDataModelsContext::DartsPointSingleColumnDataModel
{
public:
    DefaultPointSingleColumnModel()
    {
        using namespace DartsDataModelsContext;
        _pointModelBuilderService = new dartsdatamodelpointbuilder;
        _convertPointToJsonService = new ConvertPointToJson;
    }
};

#endif // DARTSPOINTDATAMODELINJECTOR_H
