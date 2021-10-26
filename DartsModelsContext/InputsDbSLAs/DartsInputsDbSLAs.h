#ifndef DARTSINPUTSDBSLAS_H
#define DARTSINPUTSDBSLAS_H

#include "IDartsInputsDbContext.h"
#include "iremovedartsinputsfromdb.h"
#include "DartsModelsContext/InputsDbSLAs/igetdartsinput.h"
#include "DartsModelsContext/InputsDbSLAs/igetinputmodelsservice.h"

class DartsInputsDbSLAs
{
public:
    IDartsInputsDbContext *inputsDb() const
    {
        return _inputsDb;
    }
    void setInputsDbContext(IDartsInputsDbContext *context)
    {
        _inputsDb = context;
    }
    IGetInputModelsService *getInputsFromDb() const
    {
        return _getInputsFromDb;
    }
    void setGetInputsFromDb(IGetInputModelsService *newGetInputsFromDb)
    {
        _getInputsFromDb = newGetInputsFromDb;
    }
    IGetDartsInput *getInputFromDb() const
    {
        return _getInputFromDb;
    }
    void setGetInputFromDb(IGetDartsInput *newGetInputFromDb)
    {
        _getInputFromDb = newGetInputFromDb;
    }
    IDartsInputBuilder *inputBuilder() const
    {
        return _inputModelBuilder;
    }
    void setInputBuilder(IDartsInputBuilder *service)
    {
        _inputModelBuilder = service;
    }
    IDartsInputJsonBuilder *inputsJsonBuilder() const
    {
        return _inputJsonBuilder;
    }
    void setInputJsonBuilder(IDartsInputJsonBuilder *service)
    {
        _inputJsonBuilder = service;
    }
    IRemoveDartsInputsFromDb *removeInputs() const
    {
        return _removeDartsInputsFromDb;
    }
    void setRemoveInputsFromDb(IRemoveDartsInputsFromDb *newRemoveDartsInputsFromDb)
    {
        _removeDartsInputsFromDb = newRemoveDartsInputsFromDb;
    }
private:
    IRemoveDartsInputsFromDb* _removeDartsInputsFromDb;
    IDartsInputsDbContext *_inputsDb;
    IDartsInputBuilder *_inputModelBuilder;
    IDartsInputJsonBuilder *_inputJsonBuilder;
    IGetInputModelsService* _getInputsFromDb;
    IGetDartsInput *_getInputFromDb;
};
#endif // DARTSINPUTSDBSLAS_H
