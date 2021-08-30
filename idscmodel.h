#ifndef IDSCMODEL_H
#define IDSCMODEL_H

#include <quuid.h>
#include <qbytearray.h>
namespace DSCContext {
    class IDSCModel
    {
    public:
        typedef QUuid Id;
        typedef QString String;
        typedef QByteArray Json;
        virtual ~IDSCModel() = default;
        virtual int score() const = 0;
        virtual Id playerId() const = 0;
        virtual String playerName() const = 0;
        virtual void setPlayerId(const Id &newPlayerId) = 0;
        virtual void setPlayerName(const String &newPlayerName) = 0;
        virtual void setScore(int newScore) = 0;
        virtual Json toJson() const = 0;
        virtual int totalScore() const = 0;
        virtual void setTotalScore(const int& totalScore) = 0;
        virtual Id tournamentId() const = 0;
        virtual void setTournamentId(const Id& id) = 0;
    };
}

#endif // IDARTSCONTROLLERSCORE_H
