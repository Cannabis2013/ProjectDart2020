#ifndef DCLOGISTICDB_H
#define DCLOGISTICDB_H

#include "idartsfinishesdb.h"
class DCLogisticDb : public IDartsFinishesDb
{
public:
    static DCLogisticDb *createInstance()
    {
        return new DCLogisticDb;
    }
    void add(const TargetRows *targetRows) override
    {
        _allTargetRows.append(targetRows);
    }
    void add(const QVector<const TargetRows*> multipleTargetRows) override
    {
        for (const auto &targetRows : multipleTargetRows)
            _allTargetRows.append(targetRows);
    }
    const TargetRows *model(const int &index) const override
    {
        return _allTargetRows.at(index);
    }
    QVector<const TargetRows *> models() const override
    {
        return _allTargetRows;
    }
    bool remove(const int &index) override
    {
        try {
            _allTargetRows.remove(index);
        }  catch (...) {
            return false;
        }
        return true;
    }
    int indexOf(const TargetRows *targetRows) const override
    {
        return _allTargetRows.indexOf(targetRows);
    }
    void replace(const int &index, const TargetRows *targetRows) override
    {
        _allTargetRows.replace(index,targetRows);
    }
    void fetchModels() override
    {
        Q_UNIMPLEMENTED();
    }
    void saveState() override
    {
        Q_UNIMPLEMENTED();
    }
private:
    QVector<const TargetRows*> _allTargetRows;
};

#endif // DARTSLOGISTICSDB_H
