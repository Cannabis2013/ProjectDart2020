#include "dartspointjsondbservice.h"

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

void DartsPointJsonDbService::addDartsInputModel(const IDartsPointInput *model)
{
    _dartsPointModels.append(model);
    saveState();
}

const IDartsPointInput *DartsPointJsonDbService::getDartsInputModelByIndex(const int &index) const
{
    auto model = _dartsPointModels.at(index);
    return model;
}

QVector<const IDartsPointInput *> DartsPointJsonDbService::dartsInputModels() const
{
    return _dartsPointModels;
}

void DartsPointJsonDbService::removeDartsInputModelByIndex(const int &index)
{
    _dartsPointModels.remove(index);
    saveState();
}

int DartsPointJsonDbService::indexOfDartsInputModel(const IDartsPointInput *score)
{
    auto index = _dartsPointModels.indexOf(score);
    return index;
}

void DartsPointJsonDbService::replaceDartsInputModel(const int &index, const IDartsPointInput *score)
{
    _dartsPointModels.replace(index,score);
    saveState();
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
