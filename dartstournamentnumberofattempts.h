#ifndef DARTSTOURNAMENTNUMBEROFATTEMPTS_H
#define DARTSTOURNAMENTNUMBEROFATTEMPTS_H

#include "idartstournamentnumberofattempts.h"
#include "abstractdartstournament.h"
class DartsTournamentNumberOfAttempts : public IDartsTournamentNumberOfAttempts
{
public:
    virtual int numberOfAttempts(const ITournament *tournament) const override
    {
        auto dartsTournament = dynamic_cast<const AbstractDartsTournament*>(tournament);
        return dartsTournament->attempts();
    }
};

#endif // DARTSTOURNAMENTNUMBEROFATTEMPTS_H
