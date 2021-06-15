#ifndef IDARTSCONTROLLERPOINT_H
#define IDARTSCONTROLLERPOINT_H

#include "ijsonmodelsservice.h"

namespace DartsPointControllerContext
{
    template<typename TUuid, typename TString, typename TJsonFormat>
    class IDartsControllerPoint : public IJsonModelsService<TJsonFormat>
    {
    public:
        virtual int point() const = 0;
        virtual void setPoint(const int& point) = 0;
        virtual int score() const = 0;
        virtual void setScore(const int& score) = 0;
        virtual TUuid playerId() const = 0;
        virtual void setPlayerId(const TUuid& id) = 0;
        virtual TString playerName() const = 0;
        virtual void setPlayerName(const TString& name) = 0;
        virtual int totalScore() const = 0;
        virtual void setTotalScore(const int& score) = 0;
        virtual TUuid tournamentId() const = 0;
        virtual void setTournamentId(const TUuid& id) = 0;
        virtual int modKeyCode() const = 0;
        virtual void setModKeyCode(const int& keyCode) = 0;
    };
}

#endif // IDARTSCONTROLLERPOINT_H
