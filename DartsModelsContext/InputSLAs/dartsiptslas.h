#ifndef DARTSIPTSLAS_H
#define DARTSIPTSLAS_H
#include "DartsModelsContext/InputSLAs/icountinputmodels.h"
#include "DartsModelsContext/InputSLAs/isortinputmodels.h"
#include "icreatemodelvalues.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsModelsContext/InputModels/diptvals.h"
class DartsIptSLAs
{
public:
    typedef IModel<QUuid> Model;
    typedef AbstractDartsInput IptModel;
    typedef IDbContext<Model> DbCtx;
    typedef ICreateModelValues<IptModel,DIptVals> CreateInputValues;
    ISortInputModels *sortInputs() const {return _sortInputs;}
    void setSortInputs(ISortInputModels *service) {_sortInputs = service;}
    ICountInputModels<DbCtx> *countInputs() const {return _countInputs;}
    void setCountInputs(ICountInputModels<DbCtx> *service) {_countInputs = service;}
    IModelPredicate *sortInputsByIndexes() const {return _sortInputsByIndexes;}
    void setSortInputsByIndexes(IModelPredicate *predicate) {_sortInputsByIndexes = predicate;}
    CreateInputValues *createInputValues() const {return _createInputValues;}
    void setCreateInputValues(CreateInputValues *newCreateInputValues) {_createInputValues = newCreateInputValues;}
private:
    ISortInputModels* _sortInputs;
    ICountInputModels<DbCtx>* _countInputs;
    IModelPredicate* _sortInputsByIndexes;
    CreateInputValues *_createInputValues;
};
#endif // DARTSIPTSLAS_H
