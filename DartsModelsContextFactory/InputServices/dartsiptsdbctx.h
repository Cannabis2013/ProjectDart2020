#ifndef DARTSIPTSDBCTX_H
#define DARTSIPTSDBCTX_H
#include "TournamentsDbSLAs/persistenceslas.h"
#include <QMutexLocker>
#include <qmutex.h>
#include <qdebug.h>
#include <QtConcurrent/QtConcurrent>
class DartsIptsDbCtx : public IDbContext<IModel<QUuid>>
{
public:
    void add(IModel<QUuid> *model) override {_models << model;}
    IModel<QUuid> *model(const int &index) const override
    {
        auto model = _models.at(index);
        return model;
    }
    IModel<QUuid>* model(std::function<bool (IModel<QUuid>*)> predFunct) const override
    {
        for (const auto &model : _models) {
            if(predFunct(model))
                return model;
        }
        return nullptr;
    }
    QVector<IModel<QUuid>*> models() const override
    {
        QVector<IModel<QUuid>*> list;
        for (const auto& model : _models)
            list << model;
        return list;
    }
    QVector<IModel<QUuid>*> models(std::function<bool (IModel<QUuid> *)> predFunct) const override
    {
        QVector<IModel<QUuid>*> models;
        for (const auto &model : _models) {
            if(predFunct(model))
                models << model;
        }
        return models;
    }
    void remove(const int &index) override {_models.remove(index);}
    void remove(const QVector<int> &indexes) override
    {
        QVector<IModel<QUuid>*> models;
        for (int i = 0; i < _models.count(); ++i) {
            if(!indexes.contains(i))
                models << _models.at(i);
        }
        _models = models;
    }
    int indexOf(IModel<QUuid>* model) const override
    {
        auto indexOfModel = _models.indexOf(model);
        return indexOfModel;
    }
    void replace(const int &index, IModel<QUuid> *model) override {_models.replace(index,model);}
private:
    QVector<IModel<QUuid>*> _models;
};
#endif // DARTSSCOREDB_H
