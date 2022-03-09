#ifndef FTPTOURNAMENTMODELINTERFACE_H
#define FTPTOURNAMENTMODELINTERFACE_H
#include "ModelSLAs/imodel.h"
template<typename T>
class QVector;
class QString;
class QUuid;
class IDartsTournament : public IModel<QUuid>
{
public:
    virtual ~IDartsTournament() = default;
    virtual int initialRemaining() const = 0;
    virtual void setKeyPoint(const int &val) = 0;
    virtual int inputHint() const = 0;
    virtual void setInputHint(const int &inputMode) = 0;
    virtual QString title() const = 0;
    virtual void setTitle(const QString &string) = 0;
    virtual int gameMode() const = 0;
    virtual void setGameMode(const int &val) = 0;
    virtual int status() const = 0;
    virtual void setStatus(const bool &active) = 0;
    virtual QUuid winnerId() const = 0;
    virtual void setWinnerId(const QUuid &val) = 0;
    virtual QString winnerName() const = 0;
    virtual void setWinnerName(const QString &name) = 0;
    virtual QVector<QUuid> &playerIds() = 0;
    virtual void setPlayerIds(const QVector<QUuid> &playerIdentities) = 0;
    virtual QVector<QString> &playerNames() = 0;
    virtual void setPlayerNames(const QVector<QString> &playerIdentities) = 0;
    virtual int totalTurns() const = 0;
    virtual void setTotalTurns(const int&) = 0;
    virtual int turnIndex() const = 0;
    virtual void setTurnIndex(const int&) = 0;
    virtual int roundIndex() const = 0;
    virtual void setRoundIndex(const int&) = 0;
    virtual int setIndex() const = 0;
    virtual void setSetIndex(const int&) = 0;
    virtual int attemptIndex() const = 0;
    virtual void setAttemptIndex(const int&) = 0;
};

#endif // FTPTOURNAMENTMODELINTERFACE_H
