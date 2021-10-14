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
        _allTargetRows.append(targetRows);
        return this;
    }
    DCLogisticDb *add(const QVector<TargetRows*> multipleTargetRows) override
    {
        for (const auto &targetRows : multipleTargetRows)
            _allTargetRows.append(targetRows);
        return this;
    }
    TargetRows *model(const int &index) const override
    {
        return _allTargetRows.at(index);
    }
    QVector<TargetRows *> models() const override
    {
        return _allTargetRows;
    }
    DCLogisticDb *remove(const int &index) override
    {
        _allTargetRows.remove(index);
        return this;
    }
    int indexOf(TargetRows *targetRows) const override
    {
        return _allTargetRows.indexOf(targetRows);
    }
    DCLogisticDb *replace(const int &index, TargetRows *targetRows) override
    {
        _allTargetRows.replace(index,targetRows);
        return this;
    }
private:
    QVector<TargetRows*> _allTargetRows;
};

#endif // DARTSLOGISTICSDB_H
