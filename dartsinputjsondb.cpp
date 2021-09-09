#include "dartsinputjsondb.h"
namespace DartsDbContext{
    void DartsInputJsonDb::add(const IModel<QUuid> *model)
    {
        _dartsScoreModels << model;
        saveState();
    }

    const IModel<QUuid> *DartsInputJsonDb::model(const int &index) const
    {
        auto model = _dartsScoreModels.at(index);
        return model;
    }

    QVector<const IModel<QUuid> *> DartsInputJsonDb::models() const
    {
        QVector<const IModel<QUuid>*> list;
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

    int DartsInputJsonDb::indexOf(const IModel<QUuid> *model) const
    {
        auto indexOfModel = _dartsScoreModels.indexOf(model);
        return indexOfModel;
    }

    void DartsInputJsonDb::replace(const int& index, const IModel<QUuid> *model)
    {
        _dartsScoreModels.replace(index,model);
        saveState();
    }

    void DartsInputJsonDb::fetchModels()
    {
        try {
            _dartsScoreModels << createModelsFromJson()->create(readJsonFromFile()->read());
        }  catch (const char *msg) {
            return;
        }
    }

    void DartsInputJsonDb::saveState()
    {
        auto json = createJsonFromModels()->toJson(_dartsScoreModels);
        writeJsonToFile()->write(json);
    }
}
