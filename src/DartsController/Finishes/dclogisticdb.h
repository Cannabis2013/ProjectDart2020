#ifndef DCLOGISTICDB_H
#define DCLOGISTICDB_H

#include "src/DartsController/Finishes/finishRow.h"
#include <qvector.h>

class DCLogisticDb
{
public:
    typedef DartsFinishes::TargetRow TargetRow;
    typedef QVector<TargetRow *> TargetRows;

    void add(TargetRows *targetRows) { _models.append(*targetRows); }

    TargetRow *model(const int &index) const { return _models.at(index); }
    TargetRow *model(std::function<bool(TargetRow *)> predFunct) const
    {
        for (const auto &model : _models) {
            if(predFunct(model))
                return model;
        }
        return nullptr;
    }
    TargetRows models() const { return _models; }
    TargetRows models(std::function<bool(TargetRow *)> predFunct) const
    {
        TargetRows m;
        for (const auto &model : _models) {
            if(predFunct(model))
                m << model;
        }
        return m;
    }
    void remove(const int &index) { _models.remove(index); }
    int indexOf(TargetRow *targetRows) const { return _models.indexOf(targetRows); }
    void replace(const int &index, TargetRow *targetRows) { _models.replace(index, targetRows); }

private:
    TargetRows _models;
};
#endif // DARTSLOGISTICSDB_H
