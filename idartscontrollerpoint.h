#ifndef IDARTSCONTROLLERPOINT_H
#define IDARTSCONTROLLERPOINT_H

#include "ijsonmodelsservice.h"

namespace DartsPointSingleAttemptContext
{
    template<typename TUuid, typename TString, typename TJsonFormat>
    class IDartsControllerPoint : public IJsonModelsService<TJsonFormat>
    {
    public:
        virtual int point() const = 0;
        virtual TUuid playerId() const = 0;
        virtual TString playerName() const = 0;
        virtual void setPlayerName(const TString& name) = 0;
        virtual int accumulatedScore() const = 0;
        virtual void setAccumulatedScore(const int& score) = 0;
        virtual TUuid tournamentId() const = 0;
        virtual void setTournamentId(const TUuid& id) = 0;
        virtual int modKeyCode() const = 0;
    };
}

#endif // IDARTSCONTROLLERPOINT_H
