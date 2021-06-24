#ifndef IDARTSCONTROLLERSCORE_H
#define IDARTSCONTROLLERSCORE_H

namespace DartsScoreControllerContext {
    template<typename TUuid, typename TString, typename TJsonFormat>
    class IDartsControllerScore
    {
    public:
        typedef TUuid IdFormat;
        typedef TString StringFormat;
        typedef TJsonFormat JsonFormat;
        virtual int score() const = 0;
        virtual IdFormat playerId() const = 0;
        virtual StringFormat playerName() const = 0;
        virtual void setPlayerId(const IdFormat &newPlayerId) = 0;
        virtual void setPlayerName(const StringFormat &newPlayerName) = 0;
        virtual void setScore(int newScore) = 0;
        virtual JsonFormat toJson() const = 0;
        virtual int totalScore() const = 0;
        virtual void setTotalScore(const int& totalScore) = 0;
        virtual IdFormat tournamentId() const = 0;
        virtual void setTournamentId(const IdFormat& id) = 0;
    };
}

#endif // IDARTSCONTROLLERSCORE_H
