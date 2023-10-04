#ifndef DCFINISHBUILDER_H
#define DCFINISHBUILDER_H

#include "dartscreatefinishes.h"
#include "dclogisticdb.h"

#include <qstring.h>

class DCFinishBuilder
{
public:
    DCFinishBuilder();
    QString suggestTargetRow(const int &remainingScore, const int &turnIndex) const;

private:
    QString getTargetRow(const int &turnIndex, const int &remainingScore) const;
    DCLogisticDb *_dbContext = new DCLogisticDb();
    DartsCreateFinishes *_constructRow = new DartsCreateFinishes();
};
#endif // SCORECONTROLLER_H

