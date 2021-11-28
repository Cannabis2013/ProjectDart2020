#ifndef DARTSIPTDBSLAS_H
#define DARTSIPTDBSLAS_H
#include <qjsonobject.h>
#include "ModelsContext/DbSLAs/icreatemodelsfrom.h"
#include "idartsinputbuilder.h"
#include "iremovedartsinputs.h"
#include "DartsModelsContext/InputsDbSLAs/igetinputs.h"
#include "ModelsContext/DbSLAs/icreatedatafrom.h"
class DartsiptDbSLAs
{
public:
    typedef QUuid Uuid;
    typedef IModel<Uuid> BaseModel;
    typedef AbstractDartsInput DartsInput;
    typedef QByteArray JsonFormat;
    IDbContext<BaseModel> *inputsDb() const {return _inputsDb;}
    void setInputsDb(IDbContext<BaseModel> *context) {_inputsDb = context;}
    IGetInputs<BaseModel,DartsInput> *getInputsFromDb() const {return _getInputsFromDb;}
    void setGetInputsFromDb(IGetInputs<BaseModel,DartsInput> *newGetInputsFromDb) {_getInputsFromDb = newGetInputsFromDb;}
    IDartsInputBuilder<BaseModel,DartsInput,JsonFormat> *inputBuilder() const {return _inputModelBuilder;}
    void setInputBuilder(IDartsInputBuilder<BaseModel,DartsInput,JsonFormat> *service) {_inputModelBuilder = service;}
    IRemoveDartsInputs<BaseModel,Uuid> *removeInputs() const {return _removeDartsInputsFromDb;}
    void setRemoveInputsFromDb(IRemoveDartsInputs<BaseModel,Uuid> *removeContext) {_removeDartsInputsFromDb = removeContext;}
    ICreateDataFrom<IModel<QUuid>,JsonFormat> *inputsToJson() const {return _inputsToJson;}
    void setInputsToJson(ICreateDataFrom<IModel<QUuid>,JsonFormat> *newIptConverter) {_inputsToJson = newIptConverter;}
private:
    ICreateDataFrom<IModel<QUuid>,JsonFormat> *_inputsToJson;
    IRemoveDartsInputs<BaseModel,Uuid>* _removeDartsInputsFromDb;
    IDartsInputBuilder<BaseModel,DartsInput,JsonFormat> *_inputModelBuilder;
    IGetInputs<BaseModel,DartsInput>* _getInputsFromDb;
    IDbContext<BaseModel> *_inputsDb;
};
#endif // DARTSIPTDBSLAS_H
