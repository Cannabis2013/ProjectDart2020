#include "dartspointjsondbservice.h"

using namespace DartsModelsContext;

DartsPointJsonDbService *DartsPointJsonDbService::createInstance(JsonExtractor* extractor,
                                                                 JsonAssembler* assembler)
{

    auto dbService = new DartsPointJsonDbService;
    dbService->setDartsPointsExtractorService(extractor);
    dbService->setDartsPointsJsonAssemblerService(assembler);
    dbService->fetchModels();
    return dbService;
}

void DartsPointJsonDbService::fetchModels()
{
    QJsonObject jsonObject;
    // Extact content from file
    try {
        jsonObject = readJsonObjectFromFile(_fileName);
    } catch (...) {
        return;
    }
    auto dartsPointsJson = jsonObject["DartsPoints"].toArray();
    _dartsPointModels << _dartsPointsExtractor->service(dartsPointsJson);
}

void DartsPointJsonDbService::saveState()
{
    /*
     * Persist tournament models
     */
    QJsonObject modelJson;
    /*
     * Persist 'first to post' tournaments
     */
    modelJson["DartsPoints"] = _dartsPointsJsonAssemblerService->service(_dartsPointModels);
    writeJsonObjectToFile(modelJson,_fileName);
}

void DartsPointJsonDbService::addModel(const Model *model)
{
    _dartsPointModels.append(model);
    saveState();
}

const DartsPointJsonDbService::Model *DartsPointJsonDbService::getModelByIndex(const int &index) const
{
    auto model = _dartsPointModels.at(index);
    return model;
}

QVector<const DartsPointJsonDbService::Model *> DartsPointJsonDbService::models() const
{
    return _dartsPointModels;
}

bool DartsPointJsonDbService::removeModelByIndex(const int &index)
{
    if(index >= _dartsPointModels.count() || index < 0)
        return false;
    _dartsPointModels.remove(index);
    saveState();
    return true;
}

int DartsPointJsonDbService::indexOfModel(const Model *score)
{
    auto index = _dartsPointModels.indexOf(score);
    return index;
}

void DartsPointJsonDbService::replaceModel(const int &index, const Model *point)
{
    _dartsPointModels.replace(index,point);
    saveState();
}

const DartsPointJsonDbService::Model *DartsPointJsonDbService::modelByIndex(const int &index) const
{
    auto model = _dartsPointModels.at(index);
    return model;
}

DartsPointJsonDbService *DartsPointJsonDbService::setDartsPointsExtractorService(JsonExtractor *dartsPointsExtractor)
{
    _dartsPointsExtractor = dartsPointsExtractor;
    return this;
}

DartsPointJsonDbService *DartsPointJsonDbService::setDartsPointsJsonAssemblerService(JsonAssembler *dartsSingleAttemptPointInputAssembler)
{
    _dartsPointsJsonAssemblerService = dartsSingleAttemptPointInputAssembler;
    return this;
}
