#ifndef DARTSTOURNAMENTNUMBEROFATTEMPTS_H
#define DARTSTOURNAMENTNUMBEROFATTEMPTS_H

#include "idartstournamentnumberofattempts.h"
#include "idartstournament.h"
class DartsTournamentNumberOfAttempts : public IDartsTournamentNumberOfAttempts
{
public:
    virtual int numberOfAttempts(const ITournament *tournament) const override
    {
        auto dartsTournament = dynamic_cast<const IDartsTournament*>(tournament);
        return dartsTournament->attempts();
    }
};

#endif // DARTSTOURNAMENTNUMBEROFATTEMPTS_H
