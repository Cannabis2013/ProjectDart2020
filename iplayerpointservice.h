#ifndef IPLAYERPOINTSERVICE_H
#define IPLAYERPOINTSERVICE_H

#include <quuid.h>
#include <qvector.h>

template<typename TPlayerDetails, typename TDartsPointModel>
class IPlayerPointService
{
public:
    typedef TPlayerDetails PlayerModel;
    typedef TDartsPointModel PointModel ;
    virtual QUuid winnerId() const = 0;
    virtual IPlayerPointService* setWinner(const QUuid& id) = 0;
    virtual QString winnerName() const = 0;

    virtual void addPlayerEntity(const PlayerModel* model) = 0;
    virtual void addPlayerEntitiesByModels(const QVector<const PlayerModel*>& models) = 0;
    virtual void subtractPlayerScoresByModels(const QVector<const PointModel*>& models) = 0;
    virtual int subtractPlayerScore(const PointModel* model) = 0;
    virtual int addPlayerScore(const PointModel* model) = 0;

    virtual int playerScore(const int& index) const = 0;
    virtual int playerScore(const QUuid&) const = 0;
    virtual void setPlayerScoreByIndex(const int &index, const int &input) = 0;
    virtual void setPlayerScoresByList(const QVector<int>& list) = 0;
    virtual void setPlayerScoreById(const QUuid &id, const int &input) = 0;

    virtual QString playerName(const int &index) const = 0;
    virtual QString playerName(const QUuid& id) const = 0;
    virtual QVector<QString> playerNames() const = 0;
    virtual QUuid playerIdAtIndex(const int &index) const = 0;

    virtual int playersCount() const = 0;
    virtual int initialScore() const = 0;
    virtual int calculateAccumulatedScoreCandidate(const int& index, const int& score) const = 0;
    virtual void resetScores() = 0;
};

#endif // IPLAYERPOINTSERVICE_H
