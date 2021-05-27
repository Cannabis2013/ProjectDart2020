#ifndef IPLAYERPOINTSERVICE_H
#define IPLAYERPOINTSERVICE_H

#include <quuid.h>
#include "dartspointmodels.h"

template<typename TPlayerDetails>
class IPlayerPointService
{
public:
    typedef TPlayerDetails PlayerDetails;
    virtual QUuid winnerId() const = 0;
    virtual IPlayerPointService* setWinner(const QUuid& id) = 0;
    virtual QString winnerUserName() const = 0;

    virtual void addPlayerEntity(const QUuid&,const QString&) = 0;
    virtual int subtractPlayerScore(const QUuid& playerId, const int& score) = 0;
    virtual int addPlayerScore(const QUuid&, const int&) = 0;

    virtual int playerScore(const int& index) const = 0;
    virtual int playerScore(const QUuid&) const = 0;
    virtual void setPlayerScoreByIndex(const int &index, const int &input) = 0;
    virtual void setPlayerScoresByList(const QVector<int>& list) = 0;
    virtual void setPlayerScoreById(const QUuid &id, const int &input) = 0;

    virtual QString playerNameByIndex(const int &index) const = 0;
    virtual QString playerNameById(const QUuid& id) const = 0;
    virtual QVector<QString> playerNames() const = 0;
    virtual QUuid playerIdAtIndex(const int &index) const = 0;

    virtual int playersCount() const = 0;
    virtual int initialScore() const = 0;
    virtual int calculateAccumulatedScoreCandidate(const int& index, const int& score) const = 0;
    virtual void resetScores() = 0;
};

#endif // IPLAYERPOINTSERVICE_H
