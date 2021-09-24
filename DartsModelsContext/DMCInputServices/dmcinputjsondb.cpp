#include "DartsModelsContext/DMCInputServices/dmcinputjsondb.h"
namespace DartsDbContext{
    void DMCInputJsonDb::add(const IModel<QUuid> *model)
    {
        _dartsScoreModels << model;
        saveState();
    }

    const IModel<QUuid> *DMCInputJsonDb::model(const int &index) const
    {
        auto model = _dartsScoreModels.at(index);
        return model;
    }

    QVector<const IModel<QUuid> *> DMCInputJsonDb::models() const
    {
        QVector<const IModel<QUuid>*> list;
        for (const auto& model : _dartsScoreModels)
            list << model;
        return list;
    }

    bool DMCInputJsonDb::remove(const int& index)
    {
        if(index >= _dartsScoreModels.count() || index < 0)
            return false;
        _dartsScoreModels.remove(index);
        saveState();
        return true;
    }

    int DMCInputJsonDb::indexOf(const IModel<QUuid> *model) const
    {
        auto indexOfModel = _dartsScoreModels.indexOf(model);
        return indexOfModel;
    }

    void DMCInputJsonDb::replace(const int& index, const IModel<QUuid> *model)
    {
        _dartsScoreModels.replace(index,model);
        saveState();
    }

    void DMCInputJsonDb::fetchModels()
    {
        try {
            _dartsScoreModels << createModelsFromJson()->create(readJsonFromFile()->read());
        }  catch (const char *msg) {
            return;
        }
    }

    void DMCInputJsonDb::saveState()
    {
        auto json = createJsonFromModels()->toJson(_dartsScoreModels);
        writeJsonToFile()->write(json);
    }
}
