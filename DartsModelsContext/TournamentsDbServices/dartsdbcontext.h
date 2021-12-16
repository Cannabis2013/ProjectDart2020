#ifndef DARTSDBCONTEXT_H
#define DARTSDBCONTEXT_H
#include <quuid.h>
#include <qvector.h>
#include "DartsModelsContext/ModelSLAs/imodel.h"
#include "DartsModelsContext/DbSLAs/idbcontext.h"
class DartsDbContext : public IDbContext<IModel<QUuid>>
{
public:
    virtual void add(IModel<QUuid> *model) override {_models.append(model);}
    virtual IModel<QUuid> *model(const int &index) const override {return modelByIndex(index);}
    IModel<QUuid>* model(std::function<bool (IModel<QUuid>*)> predFunct) const override
    {
        for (const auto &model : _models) {
            if(predFunct(model))
                return model;
        }
        return nullptr;
    }
    virtual QVector<IModel<QUuid>*> models() const override {return _models;}
    virtual QVector<IModel<QUuid>*> models(std::function<bool (IModel<QUuid> *)> predFunct) const override
    {
        QVector<IModel<QUuid>*> models;
        for (const auto &model : _models) {
            if(predFunct(model))
                models << model;
        }
        return models;
    }
    virtual void remove(const int &index) override {_models.removeAt(index);}
    virtual void remove(const QVector<int> &indexes) override
    {
        QVector<IModel<QUuid>*> models;
        for (int i = 0; i < _models.count(); ++i) {
            if(!indexes.contains(i))
                models << _models.at(i);
        }
        _models = models;
    }
    virtual int indexOf(IModel<QUuid> *model) const override
    {
        auto index = _models.indexOf(model);
        return index;
    }
    virtual void replace(const int &index, IModel<QUuid> *model) override {_models.replace(index,model);}
private:
    IModel<QUuid> *modelByIndex(const int &idx) const
    {
        auto lastMdlIdx = _models.count() - 1;
        if(idx < 0 || idx > lastMdlIdx)
            return nullptr;
        return _models.at(idx);
    }
    QVector<IModel<QUuid>*> _models;
};
#endif // DARTSTOURNAMENTJSONDB_H
