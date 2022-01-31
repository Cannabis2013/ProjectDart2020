#ifndef DARTSINPUTSERVICES_H
#define DARTSINPUTSERVICES_H
#include "InputSLAs/icountinputmodels.h"
#include "InputSLAs/isortinputmodels.h"
#include "InputModelsSLAs/idartsinput.h"
#include <qjsonobject.h>
#include "InputsDbSLAs/idartsinputbuilder.h"
#include "InputsDbSLAs/igetinputs.h"
#include "InputsDbSLAs/iremovedartsinputs.h"
#include "DbSLAs/idbjsonbuilder.h"
#include "DbSLAs/imodelconverter.h"
#include "InputModelsSLAs/idartsinputstojson.h"
#include "DbSLAs/iconvertfromdata.h"
#include "IDartsSetIptHint.h"
#include "idartsaddinputtodb.h"
#include "idartsinputtojson.h"
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
    typedef IDartsInputToJson<BaseModel> InputToJson;
    typedef IGetInputs<BaseModel,Index,Meta> GetInputs;
    typedef IDartsSetIptHint<BaseModel> SetInputHint;
    typedef IRemoveDartsInputs<BaseModel> RemoveInputs;
    typedef IModel<QUuid> Model;
    typedef IDartsInput IptModel;
    typedef IDbJsonBuilder<Model> DbInputsToJson;
    typedef IDartsInputsToJson<Model> InputsJsonBuilder;
    typedef IConvertFromData<BaseModel> ConvertFromByteArray;
    ISortInputModels *sortInputs() const {return _sortInputs;}
    void setSortInputs(ISortInputModels *service) {_sortInputs = service;}
    ICountInputModels<DbCtx> *countInputs() const {return _countInputs;}
    void setCountInputs(ICountInputModels<DbCtx> *service) {_countInputs = service;}
    IModelPredicate *sortInputsByIndexes() const {return _sortInputsByIndexes;}
    void setSortInputsByIndexes(IModelPredicate *predicate) {_sortInputsByIndexes = predicate;}
    DbCtx *inputsDb() const {return _inputsDb;}
    void setInputsDb(DbCtx *context) {_inputsDb = context;}
    GetInputs *getInputsFromDb() const {return _getInputsFromDb;}
    void setGetInputsFromDb(GetInputs *service) {_getInputsFromDb = service;}
    InputBuilder *inputBuilder() const {return _inputModelBuilder;}
    void setInputBuilder(InputBuilder *service) {_inputModelBuilder = service;}
    RemoveInputs *removeInputs() const {return _removeDartsInputsFromDb;}
    void setRemoveInputsFromDb(RemoveInputs *removeContext) {_removeDartsInputsFromDb = removeContext;}
    InputConverter *inputConverter() const {return _inputConverter;}
    void setInputConverter(InputConverter *service) {_inputConverter = service;}
    DbInputsToJson *inputModelsToJson() const {return _inputModelsToJson;}
    void setInputModelsToJson(DbInputsToJson *service) {_inputModelsToJson = service;}
    InputsJsonBuilder *createJsonFromInputs() const {return _createJsonFromInputs;}
    void setCreateJsonFromInputs(InputsJsonBuilder *service) {_createJsonFromInputs = service;}
    ConvertFromByteArray *jsonToInputs() const {return _jsonToInputs;}
    void setJsonToInputs(ConvertFromByteArray *service) {_jsonToInputs = service;}
    SetInputHint *setInputHint() const {return _setInputHint;}
    void setSetInputHint(SetInputHint *service) {_setInputHint = service;}
    IDartsAddInputToDb *addInputToDb() const {return _addInputToDb;}
    void setAddInputToDb(IDartsAddInputToDb *service) {_addInputToDb = service;}
    InputToJson *inputToJson() const {return _inputToJson;}
    void setInputToJson(InputToJson *service) {_inputToJson = service;}
private:
    SetInputHint *_setInputHint;
    ISortInputModels* _sortInputs;
    ICountInputModels<DbCtx>* _countInputs;
    IModelPredicate* _sortInputsByIndexes;
    DbInputsToJson *_inputModelsToJson;
    InputsJsonBuilder *_createJsonFromInputs;
    InputConverter *_inputConverter;
    RemoveInputs* _removeDartsInputsFromDb;
    ConvertFromByteArray *_jsonToInputs;
    InputBuilder *_inputModelBuilder;
    GetInputs* _getInputsFromDb;
    IDartsAddInputToDb *_addInputToDb;
    InputToJson *_inputToJson;
    DbCtx *_inputsDb;

};
#endif // DARTSINPUTSERVICES_H
