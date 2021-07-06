#ifndef GETDATAFROMDARTSTOURNAMENT_H
#define GETDATAFROMDARTSTOURNAMENT_H

#include "igetdatafromdartstournament.h"
#include "idartstournament.h"
class GetDataFromDartsTournament : public IGetDataFromDartsTournament<ITournament>
{
public:
    virtual int inputHint(const ITournament *tournament) const override
    {
        auto dartsTournamentModel = dynamic_cast<const IDartsTournament*>(tournament);
        auto hint = dartsTournamentModel->inputHint();
        return hint;
    }
};

#endif // GETDATAFROMDARTSTOURNAMENT_H
