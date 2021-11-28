#ifndef DARTSIPTSLAS_H
#define DARTSIPTSLAS_H

#include "DartsModelsContext/InputSLAs/icountinputmodels.h"
#include "DartsModelsContext/InputSLAs/isortinputmodels.h"

class DartsIptSLAs
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
#endif // DARTSIPTSLAS_H
