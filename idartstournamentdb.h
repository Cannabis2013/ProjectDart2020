#ifndef IDARTSTOURNAMENTDB_H
#define IDARTSTOURNAMENTDB_H

#include <qvector.h>

template<typename TModelInterface>
class IDartsTournamentDb
{
public:
    virtual void addTournament(const TModelInterface* model) = 0;
    virtual const TModelInterface* dartsTournamentModelFromIndex(const int&) = 0;
    virtual QVector<const TModelInterface*> dartsTournaments() = 0;
    virtual void removeDartsTournamentModelByIndex(const int&) = 0;
    virtual int indexOfTournament(const TModelInterface*) = 0;
    virtual void replaceTournament(const int&, const TModelInterface*) = 0;
};

#endif // IDARTSTOURNAMENTDB_H
