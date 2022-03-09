#include "dartsinputdb.h"

DartsInputDb::DartsInputDb(const QString &key, IFileDataIO *ioDevice, IModelConverter<IModel<QUuid>> *converter)
    :SaveToStorage(key,ioDevice,converter),LoadFromStorage(key,ioDevice,converter){}

bool DartsInputDb::saveChanges()
{
    return save(_models);
}

void DartsInputDb::fetch()
{
    _models = load();
}

void DartsInputDb::add(IModel<QUuid> *model)  {_models << model;}

IModel<QUuid> *DartsInputDb::model(const int &index) const
{
    auto model = _models.at(index);
    return model;
}

IModel<QUuid> *DartsInputDb::model(std::function<bool (IModel<QUuid> *)> predFunct) const
{
    for (const auto &model : _models) {
        if(predFunct(model))
            return model;
    }
    throw new std::invalid_argument("Model not found");
}

QVector<IModel<QUuid> *> DartsInputDb::models() const
{
    QVector<IModel<QUuid>*> list;
    for (const auto& model : _models)
        list << model;
    return list;
}

QVector<IModel<QUuid> *> DartsInputDb::models(std::function<bool (IModel<QUuid> *, const int &)> predFunct) const
{
    QVector<IModel<QUuid>*> models;
    for (auto i = 0;i < _models.count();i++) {
        auto model = _models.at(i);
        if(predFunct(model,i))
            models << model;
    }
    return models;
}

void DartsInputDb::remove(const int &index) {_models.remove(index);}

void DartsInputDb::remove(const QVector<int> &indexes)
{
    QVector<IModel<QUuid>*> models;
    for (int i = 0; i < _models.count(); ++i) {
        if(!indexes.contains(i))
            models << _models.at(i);
    }
    _models = models;
}

void DartsInputDb::remove(std::function<bool (IModel<QUuid> *, const int &)> predFunc)
{
    QVector<IModel<QUuid>*> models;
    for (int i = 0; i < _models.count(); ++i) {
        auto model = _models.at(i);
        if(!predFunc(model,i))
            models << model;
    }
    _models = models;
}

int DartsInputDb::indexOf(IModel<QUuid> *model) const
{
    auto indexOfModel = _models.indexOf(model);
    return indexOfModel;
}

void DartsInputDb::replace(const int &index, IModel<QUuid> *model)
{
    _models.replace(index,model);
}

