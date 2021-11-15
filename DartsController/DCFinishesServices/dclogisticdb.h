#ifndef DCLOGISTICDB_H
#define DCLOGISTICDB_H
#include "DartsController/DCFinishesSLAs/idartsfinishesdb.h"
class DCLogisticDb : public IDartsFinishesDb
{
public:
    static DCLogisticDb *createInstance()
    {
        return new DCLogisticDb;
    }
    DCLogisticDb *add(TargetRows *targetRows) override
    {
        _models.append(targetRows);
        return this;
    }
    DCLogisticDb *add(const QVector<TargetRows*> multipleTargetRows) override
    {
        for (const auto &targetRows : multipleTargetRows)
            _models.append(targetRows);
        return this;
    }
    TargetRows *model(const int &index) const override
    {
        return _models.at(index);
    }
    TargetRows* model(std::function<bool(TargetRows*)> predFunct) const override
    {
        for (const auto &model : _models) {
            if(predFunct(model))
                return model;
        }
        return nullptr;
    }
    QVector<TargetRows *> models() const override
    {
        return _models;
    }
    QVector<TargetRows*> models(std::function<bool(TargetRows*)> predFunct) const override
    {
        QVector<TargetRows*> m;
        for (const auto &model : _models) {
            if(predFunct(model))
                m << model;
        }
        return m;
    }
    DCLogisticDb *remove(const int &index) override
    {
        _models.remove(index);
        return this;
    }
    int indexOf(TargetRows *targetRows) const override
    {
        return _models.indexOf(targetRows);
    }
    DCLogisticDb *replace(const int &index, TargetRows *targetRows) override
    {
        _models.replace(index,targetRows);
        return this;
    }
private:
    QVector<TargetRows*> _models;
};

#endif // DARTSLOGISTICSDB_H
