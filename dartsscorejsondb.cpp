#include "dartsscorejsondb.h"

DartsScoreJsonDb *DartsScoreJsonDb::createInstance(DartsScoreJsonDb::JsonExtractor *extractor,
                                                   DartsScoreJsonDb::JsonAssembler *assembler)
{
    auto dbService = new DartsScoreJsonDb;
    dbService->setDartsScoresExtractorService(extractor);
    dbService->setDartsScoresJsonAssemblerService(assembler);
    dbService->fetchModels();
    return dbService;
}

void DartsScoreJsonDb::addDartsInputModel(const IDartsScoreInput *model)
{
    _dartsScoreModels << model;
    saveState();
}

const IDartsScoreInput *DartsScoreJsonDb::getDartsInputModelByIndex(const int &index) const
{
    auto model = _dartsScoreModels.at(index);
    return model;
}

QVector<const IDartsScoreInput *> DartsScoreJsonDb::dartsInputModels() const
{
    return _dartsScoreModels;
}

void DartsScoreJsonDb::removeDartsInputModelByIndex(const int& index)
{
    _dartsScoreModels.remove(index);
    saveState();
}

int DartsScoreJsonDb::indexOfDartsInputModel(const IDartsScoreInput* model)
{
    auto indexOfModel = _dartsScoreModels.indexOf(model);
    return indexOfModel;
}

void DartsScoreJsonDb::replaceDartsInputModel(const int& index, const IDartsScoreInput* model)
{
    _dartsScoreModels.replace(index,model);
    saveState();
}

void DartsScoreJsonDb::fetchModels()
{
    QJsonObject jsonObject;
    try {
        jsonObject = readJsonObjectFromFile(_fileName);
    }  catch (const char *msg) {
        return;
    }
    _dartsScoreModels << _jsonExtractorService->service(jsonObject);
}

void DartsScoreJsonDb::saveState()
{
    auto jsonObject = _jsonAssemblerService->service(_dartsScoreModels);
    writeJsonObjectToFile(jsonObject,_fileName);
}

DartsScoreJsonDb *DartsScoreJsonDb::setDartsScoresJsonAssemblerService(JsonAssembler *dartsScoresJsonAssemblerService)
{
    _jsonAssemblerService = dartsScoresJsonAssemblerService;
    return this;
}

DartsScoreJsonDb *DartsScoreJsonDb::setDartsScoresExtractorService(JsonExtractor *dartsScoresExtractor)
{
    _jsonExtractorService = dartsScoresExtractor;
    return this;
}
