#ifndef DARTSDATAMODELPOINTBUILDER_H
#define DARTSDATAMODELPOINTBUILDER_H

#include "dartsdatamodelpoint.h"
#include "idartsdatamodelpointbuilder.h"

namespace DartsDataModelsContext {
    class dartsdatamodelpointbuilder : public IDartsDataModelPointBuilder
    {
    public:
        const DartsDataModelPoint *buildModelByValues(const int &point, const int &score) override;
        const DartsDataModelPoint *buildDefaultPointModel(const int &defaultValue = -1) override;
    };
}


#endif // DARTSDATAMODELPOINTBUILDER_H
