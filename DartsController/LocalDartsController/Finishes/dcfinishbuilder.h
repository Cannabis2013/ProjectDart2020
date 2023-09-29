#ifndef DCFINISHBUILDER_H
#define DCFINISHBUILDER_H

#include "dartscreatefinishes.h"
#include "dclogisticdb.h"

#include <DartsController/Contracts/Finishes/idcfinishbuilder.h>

class IDartsCreateFinishes;
class IDartsFinishesDb;

class DCFinishBuilder : public IDCFinishBuilder
{
public:
    DCFinishBuilder();
    virtual QString suggestTargetRow(const int &remainingScore, const int &turnIndex) const override;

private:
    QString getTargetRow(const int &turnIndex, const int &remainingScore) const;
    IDartsFinishesDb *_dbContext = new DCLogisticDb();
    IDartsCreateFinishes *_constructRow = new DartsCreateFinishes();
};
#endif // SCORECONTROLLER_H

