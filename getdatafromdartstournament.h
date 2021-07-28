#ifndef GETDATAFROMDARTSTOURNAMENT_H
#define GETDATAFROMDARTSTOURNAMENT_H

#include "igetdatafromdartstournament.h"
#include "abstractdartstournament.h"
class GetDataFromDartsTournament : public IGetDataFromDartsTournament<IModel<QUuid>>
{
public:
    virtual int inputHint(const IModel<QUuid> *tournament) const override
    {
        auto dartsTournamentModel = dynamic_cast<const AbstractDartsTournament*>(tournament);
        auto hint = dartsTournamentModel->inputHint();
        return hint;
    }
};

#endif // GETDATAFROMDARTSTOURNAMENT_H
