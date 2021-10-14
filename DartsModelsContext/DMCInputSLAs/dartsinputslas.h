#ifndef DARTSINPUTSLAS_H
#define DARTSINPUTSLAS_H

#include "DartsModelsContext/DMCInputSLAs/icountinputmodels.h"
#include "DartsModelsContext/DMCInputSLAs/isortinputmodels.h"

class DartsInputSLAs
{
public:
    ISortInputModels *sortInputs() const
    {
        return _sortInputs;
    }
    void setSortInputs(ISortInputModels *service)
    {
        _sortInputs = service;
    }
    ICountInputModels *countInputs() const
    {
        return _countInputs;
    }
    void setCountInputs(ICountInputModels *service)
    {
        _countInputs = service;
    }
    IModelPredicate *sortInputsByIndexes() const
    {
        return _sortInputsByIndexes;
    }
    void setSortInputsByIndexes(IModelPredicate *predicate)
    {
        _sortInputsByIndexes = predicate;
    }
private:
    ISortInputModels* _sortInputs;
    ICountInputModels* _countInputs;
    IModelPredicate* _sortInputsByIndexes;

};
#endif // DARTSINPUTSLAS_H
