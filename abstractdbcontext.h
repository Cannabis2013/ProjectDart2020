#ifndef ABSTRACTDATABASECONTEXT_H
#define ABSTRACTDATABASECONTEXT_H

#include <qhash.h>
#include <qlist.h>
#include <quuid.h>
#include "gamemodelscontext.h"

template<class TTournament,class TRound, class TSet, class TScore,typename TUuid>
class AbstractDBContext
{
public:
    virtual void addTournament(const TTournament &tournament) = 0;
    virtual const TTournament* getTournamentFromID(const TUuid &tournament) = 0;
    virtual void replaceTournament(const TUuid &tournament, const TTournament *tournamentModel) = 0;
    virtual void removeTournamentFromID(const TUuid &tournament) = 0;
    virtual QList<const TTournament*> tournaments();

    virtual void addRound(const TRound &round) = 0;

};

#endif // ABSTRACTDATABASECONTEXT_H
