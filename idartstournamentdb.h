#ifndef IDARTSTOURNAMENTDB_H
#define IDARTSTOURNAMENTDB_H

#include <qvector.h>
#include "idartstournament.h"
#include "ipersistence.h"

class IDartsTournamentDb : public IPersistence
{
public:
    virtual void addTournament(const IDartsTournament* model) = 0;
    virtual const IDartsTournament* dartsTournamentModelFromIndex(const int&) const = 0;
    virtual QVector<const IDartsTournament*> dartsTournaments() const = 0;
    virtual void removeDartsTournamentModelByIndex(const int&) = 0;
    virtual int indexOfTournament(const IDartsTournament*) const = 0;
    virtual void replaceTournament(const int&, const IDartsTournament*) = 0;
};

#endif // IDARTSTOURNAMENTDB_H
