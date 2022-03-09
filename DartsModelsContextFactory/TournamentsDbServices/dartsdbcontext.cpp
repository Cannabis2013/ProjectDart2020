#include "dartsdbcontext.h"

DartsDbContext::DartsDbContext(const QString &key, IFileDataIO *ioDevice, IModelConverter<IModel<QUuid> > *converter)
    :SaveToStorage(key,ioDevice,converter),LoadFromStorage(key,ioDevice,converter){}

void DartsDbContext::add(IModel<QUuid> *model) {_models.append(model);}

IModel<QUuid> *DartsDbContext::model(const int &index) const {return modelByIndex(index);}

IModel<QUuid> *DartsDbContext::model(std::function<bool (IModel<QUuid> *)> predFunct) const
{
    for (const auto &model : _models) {
        if(predFunct(model))
            return model;
    }
    return nullptr;
}

QVector<IModel<QUuid> *> DartsDbContext::models() const {return _models;}

QVector<IModel<QUuid> *> DartsDbContext::models(std::function<bool (IModel<QUuid> *, const int &)> predFunct) const
{
    QVector<IModel<QUuid>*> models;
    for (int i = 0; i < _models.count(); ++i) {
        auto model = _models.at(i);
        if(predFunct(model,i))
            models << model;
    }
    return models;
}

void DartsDbContext::remove(const int &index) {_models.removeAt(index);}

void DartsDbContext::remove(const QVector<int> &indexes)
{
    QVector<IModel<QUuid>*> models;
    for (int i = 0; i < _models.count(); ++i) {
        if(!indexes.contains(i))
            models << _models.at(i);
    }
    _models = models;
}

void DartsDbContext::remove(std::function<bool (IModel<QUuid> *, const int &)> predFunc)
{
    QVector<IModel<QUuid>*> models;
    for (int i = 0; i < _models.count(); ++i) {
        auto model = _models.at(i);
        if(!predFunc(model,i))
            models << model;
    }
    _models = models;
}

int DartsDbContext::indexOf(IModel<QUuid> *model) const
{
    auto index = _models.indexOf(model);
    return index;
}

void DartsDbContext::replace(const int &index, IModel<QUuid> *model) {_models.replace(index,model);}

bool DartsDbContext::saveChanges()
{
    return save(_models);
}

void DartsDbContext::fetch()
{
    _models = load();
}

IModel<QUuid> *DartsDbContext::modelByIndex(const int &idx) const
{
    auto lastMdlIdx = _models.count() - 1;
    if(idx < 0 || idx > lastMdlIdx)
        return nullptr;
    return _models.at(idx);
}
