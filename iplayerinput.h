#ifndef ISCORE_H
#define ISCORE_H

#include "imodel.h"

template<typename TUuid>
class IPlayerInput : public IModel<TUuid>
{
public:
    IPlayerInput() {}

    virtual int hint() const = 0;
    virtual IPlayerInput* setHint(const int &hint) = 0;
    virtual TUuid playerId() const = 0;
    virtual IPlayerInput* setPlayer(const TUuid &id) = 0;
    virtual TUuid tournamentId() const = 0;
    virtual IPlayerInput* setTournamentId(const TUuid&) = 0;
};

#endif // ISCORE_H
