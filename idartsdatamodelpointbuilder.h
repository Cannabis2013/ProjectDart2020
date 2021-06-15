#ifndef IDARTSDATAMODELPOINTBUILDER_H
#define IDARTSDATAMODELPOINTBUILDER_H

#include "idatamodelpoint.h"

namespace DartsDataModelsContext {
    class IDartsDataModelPointBuilder
    {
    public:
        virtual const IDataModelPoint *buildModelByValues(const int &point, const int &score) = 0;
        virtual const IDataModelPoint *buildDefaultPointModel(const int &defaultValue = -1) = 0;
    };
}

#endif // IDARTSDATAMODELPOINTBUILDER_H
