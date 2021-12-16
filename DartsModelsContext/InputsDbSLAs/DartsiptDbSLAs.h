#ifndef DARTSIPTDBSLAS_H
#define DARTSIPTDBSLAS_H
#include <qjsonobject.h>
#include "DartsModelsContext/DbSLAs/iconverttomodels.h"
#include "idartsinputbuilder.h"
#include "iremovedartsinputs.h"
#include "DartsModelsContext/InputsDbSLAs/igetinputs.h"
#include "DartsModelsContext/DbSLAs/imodelconverter.h"
class DartsiptDbSLAs
{
public:
    typedef QUuid Uuid;
    typedef IModel<Uuid> Model;
    typedef AbstractDartsInput Input;
    typedef QByteArray Json;
    typedef IDbContext<Model> DbCtx;
    typedef DIptVals CtrlVals;
    typedef IDartsInputBuilder<Model,Input,Json,CtrlVals> InputBuilder;
    typedef IModelConverter<IModel<QUuid>,Json> JsonBuilder;
    typedef IGetInputs<Model,Input> GetInputs;
    typedef IRemoveDartsInputs<Model,Uuid,DbCtx> RemoveInputs;
    DbCtx *inputsDb() const {return _inputsDb;}
    void setInputsDb(DbCtx *context) {_inputsDb = context;}
    GetInputs *getInputsFromDb() const {return _getInputsFromDb;}
    void setGetInputsFromDb(GetInputs *newGetInputsFromDb) {_getInputsFromDb = newGetInputsFromDb;}
    InputBuilder *inputBuilder() const {return _inputModelBuilder;}
    void setInputBuilder(InputBuilder *service) {_inputModelBuilder = service;}
    RemoveInputs *removeInputs() const {return _removeDartsInputsFromDb;}
    void setRemoveInputsFromDb(RemoveInputs *removeContext) {_removeDartsInputsFromDb = removeContext;}
    JsonBuilder *inputsToJson() const {return _inputsToJson;}
    void setInputsToJson(JsonBuilder *newIptConverter) {_inputsToJson = newIptConverter;}
private:
    JsonBuilder *_inputsToJson;
    RemoveInputs* _removeDartsInputsFromDb;
    InputBuilder *_inputModelBuilder;
    GetInputs* _getInputsFromDb;
    DbCtx *_inputsDb;
};
#endif // DARTSIPTDBSLAS_H
