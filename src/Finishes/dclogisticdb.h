#ifndef DCLOGISTICDB_H
#define DCLOGISTICDB_H

#include "src/Finishes/finishestypes.h"
#include <qvector.h>

class DCLogisticDb
{
public:
        void add(FinishesTypes::TargetRows* targetRows) { _models.append(*targetRows); }

        FinishesTypes::TargetRow* model(const int& index) const
        {
                return _models.at(index);
        }

private:
        FinishesTypes::TargetRows _models;
};
#endif // DARTSLOGISTICSDB_H
