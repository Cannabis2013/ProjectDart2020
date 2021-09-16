#include "dartsinputservices.h"
IDartsInputModelsToJson *DartsInputServices::inputsToJSon() const
{
    return _inputsToJson;
}
void DartsInputServices::setInputsToJsonService(IDartsInputModelsToJson *newDartsPointsJsonService)
{
    _inputsToJson = newDartsPointsJsonService;
}
IDartsInputSetHint *DartsInputServices::dartsPointSetHint() const
{
    return _dartsPointSetHint;
}
void DartsInputServices::setDartsPointSetHint(IDartsInputSetHint *newDartsPointSetHint)
{
    _dartsPointSetHint = newDartsPointSetHint;
}
ISortInputModels *DartsInputServices::sortInputs() const
{
    return _sortInputs;
}
void DartsInputServices::setSortInputs(ISortInputModels *newSortInputs)
{
    _sortInputs = newSortInputs;
}
IGetInputModelsService *DartsInputServices::getInputsFromDb() const
{
    return _getInputsFromDb;
}
void DartsInputServices::setGetInputsFromDb(IGetInputModelsService *newGetInputsFromDb)
{
    _getInputsFromDb = newGetInputsFromDb;
}
ICountInputModels *DartsInputServices::countInputs() const
{
    return _countInputs;
}
void DartsInputServices::setCountInputs(ICountInputModels *newCountInputs)
{
    _countInputs = newCountInputs;
}
DartsInputServices::Predicate *DartsInputServices::sortInputsByIndexes() const
{
    return _sortPointInputsByIndexes;
}
void DartsInputServices::setSortInputsByIndexes(Predicate *newSortPointInputsByIndexes)
{
    _sortPointInputsByIndexes = newSortPointInputsByIndexes;
}
IGetDartsPointFromDb *DartsInputServices::getInputFromDb() const
{
    return _getInputFromDb;
}
void DartsInputServices::setGetInputFromDb(IGetDartsPointFromDb *newGetPointFromDb)
{
    _getInputFromDb = newGetPointFromDb;
}
IDartsIndexesToJson *DartsInputServices::indexesToJson() const
{
    return _indexesToJson;
}
void DartsInputServices::setIndexesToJsonService(IDartsIndexesToJson *newCreateJsonFromPointIndexes)
{
    _indexesToJson = newCreateJsonFromPointIndexes;
}
IModelsDbContext *DartsInputServices::inputsDb() const
{
    return _inputsDb;
}
void DartsInputServices::setInputsDbService(IModelsDbContext *dbService)
{
    _inputsDb = dbService;
}
IDartsCreateInput *DartsInputServices::createInputModel() const
{
    return _createPointModel;
}
void DartsInputServices::setCreatePointModel(IDartsCreateInput *newCreatePointModel)
{
    _createPointModel = newCreatePointModel;
}
IDartsCreateJsonFromModel<IModel<QUuid>> *DartsInputServices::inputToJson() const
{
    return _createJsonFromInputs;
}
void DartsInputServices::setInputToJsonService(IDartsCreateJsonFromModel<IModel<QUuid>> *newCreateJsonFromDartsPoint)
{
    _createJsonFromInputs = newCreateJsonFromDartsPoint;
}
IRemoveDartsInputsFromDb *DartsInputServices::removeInputsFromDb() const
{
    return _removeDartsInputsFromDb;
}
void DartsInputServices::setRemoveInputsFromDb(IRemoveDartsInputsFromDb *newDbManipulatorService)
{
    _removeDartsInputsFromDb = newDbManipulatorService;
}
IDartsCreateIndexes<IDartsPointIndexes> *DartsInputServices::indexesBuilder() const
{
    return _createIndexesFromInputs;
}
void DartsInputServices::setIndexesBuilder(IDartsCreateIndexes<IDartsPointIndexes> *newCreateIndexesFromPointModels)
{
    _createIndexesFromInputs = newCreateIndexesFromPointModels;
}
