#include "DartsModelsContext/DMCInputSLAs/dmcinputslas.h"
IDartsInputModelsToJson *DMCInputSLAs::inputsToJSon() const
{
    return _inputsToJson;
}
void DMCInputSLAs::setInputsToJsonService(IDartsInputModelsToJson *newDartsPointsJsonService)
{
    _inputsToJson = newDartsPointsJsonService;
}
IDartsInputSetHint *DMCInputSLAs::dartsPointInputHint() const
{
    return _dartsPointSetHint;
}
void DMCInputSLAs::setDartsPointSetHint(IDartsInputSetHint *newDartsPointSetHint)
{
    _dartsPointSetHint = newDartsPointSetHint;
}
ISortInputModels *DMCInputSLAs::sortInputs() const
{
    return _sortInputs;
}
void DMCInputSLAs::setSortInputs(ISortInputModels *newSortInputs)
{
    _sortInputs = newSortInputs;
}
IGetInputModelsService *DMCInputSLAs::getInputsFromDb() const
{
    return _getInputsFromDb;
}
void DMCInputSLAs::setGetInputsFromDb(IGetInputModelsService *newGetInputsFromDb)
{
    _getInputsFromDb = newGetInputsFromDb;
}
ICountInputModels *DMCInputSLAs::countInputs() const
{
    return _countInputs;
}
void DMCInputSLAs::setCountInputs(ICountInputModels *newCountInputs)
{
    _countInputs = newCountInputs;
}
DMCInputSLAs::Predicate *DMCInputSLAs::sortInputsByIndexes() const
{
    return _sortPointInputsByIndexes;
}
void DMCInputSLAs::setSortInputsByIndexes(Predicate *newSortPointInputsByIndexes)
{
    _sortPointInputsByIndexes = newSortPointInputsByIndexes;
}
IGetDartsInputFromDb *DMCInputSLAs::getInputFromDb() const
{
    return _getInputFromDb;
}
void DMCInputSLAs::setGetInputFromDb(IGetDartsInputFromDb *newGetPointFromDb)
{
    _getInputFromDb = newGetPointFromDb;
}
IModelsDbContext *DMCInputSLAs::inputsDb() const
{
    return _inputsDb;
}
void DMCInputSLAs::setInputsDbService(IModelsDbContext *dbService)
{
    _inputsDb = dbService;
}
IDartsCreateInput *DMCInputSLAs::createInputModel() const
{
    return _createPointModel;
}
void DMCInputSLAs::setCreatePointModel(IDartsCreateInput *newCreatePointModel)
{
    _createPointModel = newCreatePointModel;
}
IDartsCreateJsonFromModel<IModel<QUuid>> *DMCInputSLAs::inputToJson() const
{
    return _createJsonFromInputs;
}
void DMCInputSLAs::setInputToJsonService(IDartsCreateJsonFromModel<IModel<QUuid>> *newCreateJsonFromDartsPoint)
{
    _createJsonFromInputs = newCreateJsonFromDartsPoint;
}
IRemoveDartsInputsFromDb *DMCInputSLAs::removeInputsFromDb() const
{
    return _removeDartsInputsFromDb;
}
void DMCInputSLAs::setRemoveInputsFromDb(IRemoveDartsInputsFromDb *newDbManipulatorService)
{
    _removeDartsInputsFromDb = newDbManipulatorService;
}
