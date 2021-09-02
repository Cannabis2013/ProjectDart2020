#ifndef IDPCMODEL_H
#define IDPCMODEL_H

#include <quuid.h>
namespace DCContext
{
    class IDCModel
    {
    public:
        virtual ~IDCModel() = default;
        virtual int point() const = 0;
        virtual void setPoint(const int& point) = 0;
        virtual int score() const = 0;
        virtual void setScore(const int& score) = 0;
        virtual QUuid playerId() const = 0;
        virtual void setPlayerId(const QUuid& id) = 0;
        virtual QString playerName() const = 0;
        virtual void setPlayerName(const QString &name) = 0;
        virtual int totalScore() const = 0;
        virtual void setTotalScore(const int& score) = 0;
        virtual int modKeyCode() const = 0;
        virtual void setModKeyCode(const int& keyCode) = 0;
        virtual QUuid tournamentId() const = 0;
        virtual void setTournamentId(const QUuid& id) = 0;
    };
}
#endif // IDARTSCONTROLLERPOINT_H
