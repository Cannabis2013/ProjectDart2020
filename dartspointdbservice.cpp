#include "dartspointdbservice.h"

DartsPointDbService *DartsPointDbService::createInstance()
{
    return new DartsPointDbService;
}

void DartsPointDbService::fetchModels()
{
    QJsonObject jsonObject;
    // Extact content from file
    try {
        jsonObject = readJSONFromFile(_fileName);
    } catch (...) {
        return;
    }
    auto dartsPointsJson = jsonObject["DartsPoints"].toArray();
    _dartsPointModels << _dartsPointsExtractor->service(dartsPointsJson);
}

void DartsPointDbService::saveState()
{
    /*
     * Persist tournament models
     */
    QJsonObject modelJson;
    /*
     * Persist 'first to post' tournaments
     */
    modelJson["DartsPoints"] = _dartsPointsJsonAssemblerService->service(_dartsPointModels);
    writeJSONToFile(modelJson,_fileName);
}

void DartsPointDbService::addDartsInputModel(const IDartsPointInput<QUuid> *model)
{
    _dartsPointModels.append(model);
    saveState();
}

const IDartsPointInput<QUuid> *DartsPointDbService::getDartsInputModelByIndex(const int &index) const
{
    auto model = _dartsPointModels.at(index);
    return model;
}

QVector<const IDartsPointInput<QUuid> *> DartsPointDbService::dartsInputModels() const
{
    return _dartsPointModels;
}

void DartsPointDbService::removeDartsInputModelByIndex(const int &index)
{
    _dartsPointModels.remove(index);
    saveState();
}

int DartsPointDbService::indexOfDartsInputModel(const IDartsPointInput<QUuid> *score)
{
    auto index = _dartsPointModels.indexOf(score);
    return index;
}

void DartsPointDbService::replaceDartsInputModel(const int &index, const IDartsPointInput<QUuid> *score)
{
    _dartsPointModels.replace(index,score);
    saveState();
}

DartsPointDbService *DartsPointDbService::setDartsPointsExtractorService(IUnaryService<const QJsonArray &, QVector<const IDartsPointInput<QUuid> *> > *dartsPointsExtractor)
{
    _dartsPointsExtractor = dartsPointsExtractor;
    return this;
}

DartsPointDbService *DartsPointDbService::setDartsPointsJsonAssemblerService(IUnaryService<const QVector<const IDartsPointInput<QUuid> *> &, QJsonArray> *dartsSingleAttemptPointInputAssembler)
{
    _dartsPointsJsonAssemblerService = dartsSingleAttemptPointInputAssembler;
    return this;
}
