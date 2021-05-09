#ifndef IDARTSTOURNAMENTDB_H
#define IDARTSTOURNAMENTDB_H

#include <qvector.h>
#include "idartstournament.h"

class IDartsTournamentDb
{
public:
    virtual void addTournament(const IDartsTournament* model) = 0;
    virtual const IDartsTournament* dartsTournamentModelFromIndex(const int&) = 0;
    virtual QVector<const IDartsTournament*> dartsTournaments() = 0;
    virtual void removeDartsTournamentModelByIndex(const int&) = 0;
    virtual int indexOfTournament(const IDartsTournament*) = 0;
    virtual void replaceTournament(const int&, const IDartsTournament*) = 0;
};

#endif // IDARTSTOURNAMENTDB_H
