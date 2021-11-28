#include "DartsModelsContext/InputServices/dartsiptsdbctx.h"

DartsIptsDbCtx *DartsIptsDbCtx::add(IModel<QUuid> *model)
{
    QMutexLocker locker(&_mutex);
    _models << model;
    return this;
}

IModel<QUuid> *DartsIptsDbCtx::model(const int &index) const
{
    auto model = _models.at(index);
    return model;
}

IModel<QUuid> *DartsIptsDbCtx::model(std::function<bool (IModel<QUuid> *)> predFunct) const
{
    for (const auto &model : _models) {
        if(predFunct(model))
            return model;
    }
    return nullptr;
}

QVector<IModel<QUuid> *> DartsIptsDbCtx::models() const
{
    QVector<IModel<QUuid>*> list;
    for (const auto& model : _models)
        list << model;
    return list;
}

QVector<IModel<QUuid> *> DartsIptsDbCtx::models(std::function<bool (IModel<QUuid> *)> predFunct) const
{
    QVector<IModel<QUuid>*> models;
    for (const auto &model : _models) {
        if(predFunct(model))
            models << model;
    }
    return models;
}

DartsIptsDbCtx *DartsIptsDbCtx::remove(const int& index)
{
    QMutexLocker locker(&_mutex);
    _models.remove(index);
    return this;
}

IDbContext<IModel<QUuid>> *DartsIptsDbCtx::remove(const QVector<int> &indexes)
{
    QVector<IModel<QUuid>*> models;
    for (int i = 0; i < _models.count(); ++i) {
        if(!indexes.contains(i))
            models << _models.at(i);
    }
    _models = models;
    return this;
}

int DartsIptsDbCtx::indexOf(IModel<QUuid> *model) const
{
    auto indexOfModel = _models.indexOf(model);
    return indexOfModel;
}

DartsIptsDbCtx *DartsIptsDbCtx::replace(const int& index, IModel<QUuid> *model)
{
    _models.replace(index,model);
    return this;
}
