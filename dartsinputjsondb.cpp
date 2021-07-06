#include "dartsinputjsondb.h"
namespace DartsDbContext{
    DartsInputJsonDb::DartsInputJsonDb(const QString &fileName):
        _fileName(fileName)
    {
    }

    void DartsInputJsonDb::add(const Model *model)
    {
        _dartsScoreModels << model;
        saveState();
    }

    const IPlayerInput *DartsInputJsonDb::model(const int &index) const
    {
        auto model = _dartsScoreModels.at(index);
        return model;
    }

    QVector<const DartsInputJsonDb::Model *> DartsInputJsonDb::models() const
    {
        QVector<const Model*> list;
        for (const auto& model : _dartsScoreModels)
            list << model;
        return list;
    }

    bool DartsInputJsonDb::remove(const int& index)
    {
        if(index >= _dartsScoreModels.count() || index < 0)
            return false;
        _dartsScoreModels.remove(index);
        saveState();
        return true;
    }

    int DartsInputJsonDb::indexOf(const Model *model) const
    {
        auto indexOfModel = _dartsScoreModels.indexOf(model);
        return indexOfModel;
    }

    void DartsInputJsonDb::replace(const int& index, const Model *model)
    {
        _dartsScoreModels.replace(index,model);
        saveState();
    }

    void DartsInputJsonDb::fetchModels()
    {
        try {
            _dartsScoreModels << _createInputModelsFromJson->create(readJsonObjectFromFile(_fileName));
        }  catch (const char *msg) {
            return;
        }
    }

    void DartsInputJsonDb::saveState()
    {
        writeJsonObjectToFile(_createJsonFromInputModels->createJson(_dartsScoreModels),_fileName);
    }
}
