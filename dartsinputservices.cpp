#include "dartsinputservices.h"
IDartsModelsCreateJsonFromPoints *DartsInputServices::dartsPointsJsonService() const
{
    return _dartsPointsJsonService;
}
void DartsInputServices::setDartsPointsJsonService(IDartsModelsCreateJsonFromPoints *newDartsPointsJsonService)
{
    _dartsPointsJsonService = newDartsPointsJsonService;
}
IDartsPointSetHint *DartsInputServices::dartsPointSetHint() const
{
    return _dartsPointSetHint;
}
void DartsInputServices::setDartsPointSetHint(IDartsPointSetHint *newDartsPointSetHint)
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
DartsInputServices::Predicate *DartsInputServices::sortPointInputsByIndexes() const
{
    return _sortPointInputsByIndexes;
}
void DartsInputServices::setSortPointInputsByIndexes(Predicate *newSortPointInputsByIndexes)
{
    _sortPointInputsByIndexes = newSortPointInputsByIndexes;
}
IGetDartsPointFromDb *DartsInputServices::getPointFromDb() const
{
    return _getPointFromDb;
}
void DartsInputServices::setGetPointFromDb(IGetDartsPointFromDb *newGetPointFromDb)
{
    _getPointFromDb = newGetPointFromDb;
}
ICreateJsonfromDartsPointIndexes *DartsInputServices::createJsonFromPointIndexes() const
{
    return _createJsonFromPointIndexes;
}
void DartsInputServices::setCreateJsonFromPointIndexes(ICreateJsonfromDartsPointIndexes *newCreateJsonFromPointIndexes)
{
    _createJsonFromPointIndexes = newCreateJsonFromPointIndexes;
}
IModelsDbContext *DartsInputServices::inputsDb() const
{
    return _inputsDb;
}
void DartsInputServices::setInputsDb(IModelsDbContext *dbService)
{
    _inputsDb = dbService;
}

IDartsCreateInput *DartsInputServices::createPointModel() const
{
    return _createPointModel;
}

void DartsInputServices::setCreatePointModel(IDartsCreateInput *newCreatePointModel)
{
    _createPointModel = newCreatePointModel;
}

IDartsCreateJsonFromModel<IModel<QUuid>> *DartsInputServices::createJsonFromDartsPoint() const
{
    return _createJsonFromDartsPoint;
}

void DartsInputServices::setCreateJsonFromDartsPoint(IDartsCreateJsonFromModel<IModel<QUuid>> *newCreateJsonFromDartsPoint)
{
    _createJsonFromDartsPoint = newCreateJsonFromDartsPoint;
}

IRemoveDartsInputsFromDb *DartsInputServices::removeInputsFromDb() const
{
    return _removeDartsInputsFromDb;
}

void DartsInputServices::setRemoveInputsFromDb(IRemoveDartsInputsFromDb *newDbManipulatorService)
{
    _removeDartsInputsFromDb = newDbManipulatorService;
}

IDartsCreateIndexes<IDartsPointIndexes> *DartsInputServices::createControllerIndexes() const
{
    return _createIndexesFromPointModels;
}

void DartsInputServices::setCreateIndexesFromPointModels(IDartsCreateIndexes<IDartsPointIndexes> *newCreateIndexesFromPointModels)
{
    _createIndexesFromPointModels = newCreateIndexesFromPointModels;
}
