#ifndef IDARTSTOURNAMENTNUMBEROFATTEMPTS_H
#define IDARTSTOURNAMENTNUMBEROFATTEMPTS_H

#include "itournament.h"

class IDartsTournamentNumberOfAttempts
{
public:
    virtual int numberOfAttempts(const ITournament *tournament) const = 0;
};

#endif // IDARTSGETNUMBEROFATTEMPTS_H
