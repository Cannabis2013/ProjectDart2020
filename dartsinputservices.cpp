#include "dartsinputservices.h"
IDartsModelsCreateJsonFromPoints *DartsInputServices::dartsPointsJsonService() const
{
    return _dartsPointsJsonService;
}
void DartsInputServices::setDartsPointsJsonService(IDartsModelsCreateJsonFromPoints *newDartsPointsJsonService)
{
    _dartsPointsJsonService = newDartsPointsJsonService;
}
IDartsCreateJsonFromScores *DartsInputServices::createJsonFromScoreModels() const
{
    return _createJsonFromScoreModels;
}
void DartsInputServices::setCreateJsonFromScoreModels(IDartsCreateJsonFromScores *newCreateJsonFromScoreModels)
{
    _createJsonFromScoreModels = newCreateJsonFromScoreModels;
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
DartsInputServices::ScoreModelsService *DartsInputServices::dartsScoreSetHint() const
{
    return _dartsScoreSetHint;
}
void DartsInputServices::setDartsScoreSetHint(ScoreModelsService *newDartsScoreSetHint)
{
    _dartsScoreSetHint = newDartsScoreSetHint;
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
DartsInputServices::Predicate *DartsInputServices::sortScoreInputsByIndexes() const
{
    return _sortScoreInputsByIndexes;
}
void DartsInputServices::setSortScoreInputsByIndexes(Predicate *newSortScoreInputsByIndexes)
{
    _sortScoreInputsByIndexes = newSortScoreInputsByIndexes;
}
IGetDartsScoreFromDb *DartsInputServices::getScoreFromDb() const
{
    return _getScoreFromDb;
}
void DartsInputServices::setGetScoreFromDb(IGetDartsScoreFromDb *newGetScoreFromDb)
{
    _getScoreFromDb = newGetScoreFromDb;
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
IDartsCreateJsonFromScoreIndexes *DartsInputServices::createJsonfromScoreIndexes() const
{
    return _createJsonfromScoreIndexes;
}
void DartsInputServices::setCreateJsonfromScoreIndexes(IDartsCreateJsonFromScoreIndexes *newCreateJsonfromScoreIndexes)
{
    _createJsonfromScoreIndexes = newCreateJsonfromScoreIndexes;
}
IModelsDbContext *DartsInputServices::dartsPointsDb() const
{
    return _dartsPointsDb;
}
void DartsInputServices::setDartsPointsDb(IModelsDbContext *newDartsPointsDb)
{
    _dartsPointsDb = newDartsPointsDb;
}
IModelsDbContext *DartsInputServices::dartsScoresDb() const
{
    return _dartsScoresDb;
}
void DartsInputServices::setDartsScoresDb(IModelsDbContext *newDartsScoresDb)
{
    _dartsScoresDb = newDartsScoresDb;
}

IDartsCreateInput *DartsInputServices::createScoreModel() const
{
    return _createScoreModel;
}

void DartsInputServices::setCreateScoreModel(IDartsCreateInput *newCreateScoreModel)
{
    _createScoreModel = newCreateScoreModel;
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

IDartsCreateJsonFromModel<IModel<QUuid>> *DartsInputServices::createJsonFromDartsScore() const
{
    return _createJsonFromDartsScore;
}

void DartsInputServices::setCreateJsonFromDartsScore(IDartsCreateJsonFromModel<IModel<QUuid>> *newCreateJsonFromDartsScore)
{
    _createJsonFromDartsScore = newCreateJsonFromDartsScore;
}

IRemoveDartsInputsFromDb *DartsInputServices::removeInputsFromDb() const
{
    return _removeDartsInputsFromDb;
}

void DartsInputServices::setRemoveInputsFromDb(IRemoveDartsInputsFromDb *newDbManipulatorService)
{
    _removeDartsInputsFromDb = newDbManipulatorService;
}

IDartsCreateIndexes<IDartsScoreIndexes> *DartsInputServices::createIndexesFromScoreModels() const
{
    return _createIndexesFromScoreModels;
}

void DartsInputServices::setCreateIndexesFromScoreModels(IDartsCreateIndexes<IDartsScoreIndexes> *newCreateIndexesFromScoreModels)
{
    _createIndexesFromScoreModels = newCreateIndexesFromScoreModels;
}

IDartsCreateIndexes<IDartsPointIndexes> *DartsInputServices::createIndexesFromPoints() const
{
    return _createIndexesFromPointModels;
}

void DartsInputServices::setCreateIndexesFromPointModels(IDartsCreateIndexes<IDartsPointIndexes> *newCreateIndexesFromPointModels)
{
    _createIndexesFromPointModels = newCreateIndexesFromPointModels;
}
