#ifndef DARTSINPUTSERVICES_H
#define DARTSINPUTSERVICES_H

#include "icountinputmodels.h"
#include "isortinputmodels.h"

#include <qjsonobject.h>

#include <DartsModelsContext/DbSLAs/idbcontext.h>
#include <DartsModelsContext/DbSLAs/imodelconverter.h>

#include <DartsModelsContext/InputsDbSLAs/idartsinputbuilder.h>
#include <DartsModelsContext/InputsDbSLAs/igetinputs.h>
#include <DartsModelsContext/InputsDbSLAs/iremovedartsinputs.h>

struct DartsMetaModel;
class IDartsIndex;
class IDartsInput;
template<typename T>class IModel;

class DartsInputServices
{
public:
    typedef QUuid Uuid;
    typedef IModel<QUuid> BaseModel;
    typedef IDartsInput Input;
    typedef IDbContext<BaseModel> DbCtx;
    typedef IDartsInputBuilder InputBuilder;
    typedef IModelConverter<BaseModel> InputConverter;
    typedef IDartsIndex Index;
    typedef DartsMetaModel Meta;
    typedef IGetInputs<BaseModel,Index,Meta> GetInputs;
    typedef IRemoveDartsInputs<BaseModel> RemoveInputs;
    typedef IModel<QUuid> Model;
    typedef IDartsInput IptModel;
    ISortInputModels *sortInputs() const {return _sortInputs;}
    void setSortInputs(ISortInputModels *service) {_sortInputs = service;}
    ICountInputModels<DbCtx> *countInputs() const {return _countInputs;}
    void setCountInputs(ICountInputModels<DbCtx> *service) {_countInputs = service;}
    IModelPredicate *sortInputsByIndexes() const {return _sortInputsByIndexes;}
    void setSortInputsByIndexes(IModelPredicate *predicate) {_sortInputsByIndexes = predicate;}
    DbCtx *dbContext() const {return _inputsDb;}
    void setInputsDb(DbCtx *context) {_inputsDb = context;}
    GetInputs *getInputsFromDb() const {return _getInputsFromDb;}
    void setGetInputsFromDb(GetInputs *service) {_getInputsFromDb = service;}
    InputBuilder *inputBuilder() const {return _inputModelBuilder;}
    void setInputBuilder(InputBuilder *service) {_inputModelBuilder = service;}
    RemoveInputs *removeInputs() const {return _removeDartsInputsFromDb;}
    void setRemoveInputsFromDb(RemoveInputs *removeContext) {_removeDartsInputsFromDb = removeContext;}
    InputConverter *inputConverter() const {return _inputConverter;}
    void setInputConverter(InputConverter *service) {_inputConverter = service;}
private:
    ISortInputModels* _sortInputs;
    ICountInputModels<DbCtx>* _countInputs;
    IModelPredicate* _sortInputsByIndexes;
    InputConverter *_inputConverter;
    RemoveInputs* _removeDartsInputsFromDb;
    InputBuilder *_inputModelBuilder;
    GetInputs* _getInputsFromDb;
    DbCtx *_inputsDb;

};
#endif // DARTSINPUTSERVICES_H
