#ifndef DARTSINPUTSDBSLAS_H
#define DARTSINPUTSDBSLAS_H

#include "IDartsInputsDbContext.h"
#include "iremovedartsinputsfromdb.h"
#include "DartsModelsContext/InputsDbSLAs/igetdartsinputfromdb.h"
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
    IGetDartsInputFromDb *getInputFromDb() const
    {
        return _getInputFromDb;
    }
    void setGetInputFromDb(IGetDartsInputFromDb *newGetInputFromDb)
    {
        _getInputFromDb = newGetInputFromDb;
    }
    IDartsInputBuilder *inputModelBuilder() const
    {
        return _inputModelBuilder;
    }
    void setInputModelBuilder(IDartsInputBuilder *service)
    {
        _inputModelBuilder = service;
    }
    IDartsInputJsonBuilder *inputJsonBuilder() const
    {
        return _inputJsonBuilder;
    }
    void setInputJsonBuilder(IDartsInputJsonBuilder *service)
    {
        _inputJsonBuilder = service;
    }
    IRemoveDartsInputsFromDb *removeInputsFromDb() const
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
    IGetDartsInputFromDb *_getInputFromDb;
};
#endif // DARTSINPUTSDBSLAS_H
