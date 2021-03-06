#include "dartsscorejsondb.h"
namespace DartsModelsContext{
    DartsScoreJsonDb *DartsScoreJsonDb::createInstance(DartsScoreJsonDb::JsonExtractor *extractor,
                                                       DartsScoreJsonDb::JsonAssembler *assembler)
    {
        auto dbService = new DartsScoreJsonDb;
        dbService->setDartsScoresExtractorService(extractor);
        dbService->setDartsScoresJsonAssemblerService(assembler);
        dbService->fetchModels();
        return dbService;
    }

    void DartsScoreJsonDb::addModel(const IDartsInput *model)
    {
        _dartsScoreModels << dynamic_cast<const IDartsScoreInput*>(model);
        saveState();
    }

    const IDartsScoreInput *DartsScoreJsonDb::modelByIndex(const int &index) const
    {
        auto model = _dartsScoreModels.at(index);
        return model;
    }

    QVector<const IDartsInput *> DartsScoreJsonDb::models() const
    {
        QVector<const IDartsInput*> list;
        for (const auto& model : _dartsScoreModels)
            list << model;
        return list;
    }

    bool DartsScoreJsonDb::removeModelByIndex(const int& index)
    {
        if(index >= _dartsScoreModels.count() || index < 0)
            return false;
        _dartsScoreModels.remove(index);
        saveState();
        return true;
    }

    bool DartsScoreJsonDb::removeModelById(const QUuid &id)
    {
        for (const auto& model : qAsConst(_dartsScoreModels)) {
            if(model->id() == id)
            {
                _dartsScoreModels.removeOne(model);
                saveState();
                return true;
            }
        }
        return false;
    }

    int DartsScoreJsonDb::indexOfModel(const IDartsInput *model)
    {
        auto indexOfModel = _dartsScoreModels.indexOf(dynamic_cast<const IDartsScoreInput*>(model));
        return indexOfModel;
    }

    void DartsScoreJsonDb::replaceModel(const int& index, const IDartsInput *model)
    {
        _dartsScoreModels.replace(index,dynamic_cast<const IDartsScoreInput*>(model));
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

    const IDartsScoreInput *DartsScoreJsonDb::modelById(const QUuid &id) const
    {
        for (const auto& model : _dartsScoreModels) {
            if(model->id() == id)
                return model;
        }
        return nullptr;
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
}
