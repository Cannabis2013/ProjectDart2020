#include "DartsModelsContext/TournamentsDbServices/dartsdbcontext.h"

DartsDbContext *DartsDbContext::add(IModel<QUuid> *model)
{
    _models.append(model);
    return this;
}

IModel<QUuid> *DartsDbContext::model(const int &index) const
{
    auto model = _models.at(index);
    return model;
}

IModel<QUuid> *DartsDbContext::model(std::function<bool (IModel<QUuid> *)> predFunct) const
{
    for (const auto &model : _models) {
        if(predFunct(model))
            return model;
    }
    return nullptr;
}

QVector<IModel<QUuid> *> DartsDbContext::models() const
{
    return _models;
}

QVector<IModel<QUuid> *> DartsDbContext::models(std::function<bool (IModel<QUuid> *)> predFunct) const
{
    QVector<IModel<QUuid>*> models;
    for (const auto &model : _models) {
        if(predFunct(model))
            models << model;
    }
    return models;
}

DartsDbContext *DartsDbContext::remove(const int &index)
{
    _models.removeAt(index);
    return this;
}

DartsDbContext *DartsDbContext::remove(const QVector<int> &indexes)
{
    QVector<IModel<QUuid>*> models;
    for (int i = 0; i < _models.count(); ++i) {
        if(!indexes.contains(i))
            models << _models.at(i);
    }
    _models = models;
    return this;
}

int DartsDbContext::indexOf(IModel<QUuid> *model) const
{
    auto index = _models.indexOf(model);
    return index;
}

DartsDbContext *DartsDbContext::replace(const int &index, IModel<QUuid> *model)
{
    _models.replace(index,model);
    return this;
}
