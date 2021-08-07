#ifndef DARTSPLAYERPOINTSERVICE_H
#define DARTSPLAYERPOINTSERVICE_H

#include "iplayerpointservice.h"
#include <qpair.h>
#include <qvector.h>
#include <dartscontrollerplayer.h>
#include "idartscontrollerpoint.h"

#define INCONSISTENCY_EXCEPTION_MESSAGE "User inconsistency!"

namespace PlayerPointContext
{
    struct PlayerTuple
    {
        PlayerTuple(QUuid _id, QString _name, int _score)
        {
            id = _id;
            name = _name;
            score = _score;
        }
        PlayerTuple(){}

        bool operator==(const PlayerPointContext::PlayerTuple& other){
            if(other.id != this->id)
                return false;
            else if(other.name != this->name)
                return false;
            else if(other.score != this->score)
                return false;
            return true;
        }
        QUuid id;
        QString name;
        int score;
    };
}
namespace DartsPointControllerContext {
    class DartsPlayerPointService : public
            IPlayerPointService<IDartsControllerPlayer<QUuid,QString,QByteArray>,IDartsControllerPoint<QUuid,QString,QByteArray>>
    {
        // IPlayerPointService interface
    public:
        // Tuple : {UserId, UserName, UserScore}
        typedef QVector<PlayerPointContext::PlayerTuple> PlayerTuples;
        typedef QPair<QUuid,QString> PlayerPair;
        typedef QList<PlayerPair> PlayerPairs;
        typedef IDartsControllerPoint<QUuid,QString,QByteArray> PointModel;
        static DartsPlayerPointService* createInstance(const int& initialScore,
                                                  const QUuid &winner);

        QUuid winnerId() const override;
        DartsPlayerPointService *setWinner(const QUuid &id) override;
        QString winnerName() const override;
        void addPlayerEntity(const PlayerModel* model) override;
        void addPlayerEntities(const QVector<const PlayerModel*>& models) override;
        int subtractPlayerScore(const PointModel* model) override;
        void subtractPlayerScoresByModels(const QVector<const PointModel*>& models) override;
        int addPlayerScore(const PointModel* model) override;
        int playerScore(const int &index) const override;
        int playerScore(const QUuid &id) const override;
        void setPlayerScoreByIndex(const int &index, const int &input) override;
        void setPlayerScoresByList(const QVector<int> &list) override;
        void setPlayerScoreById(const QUuid &id, const int &input) override;
        QString playerName(const int &index) const override;
        QString playerName(const QUuid &id) const override;
        QVector<QString> playerNames() const override;
        QUuid playerIdAtIndex(const int &index) const override;
        int playersCount() const override;
        int initialScore() const override;
        int calculateAccumulatedScoreCandidate(const int &index, const int &score) const override;
        void resetScores() override;
    private:
        /*
         * Private constructor
         */
        DartsPlayerPointService(const int& initialScore,
                           const QUuid& winner);
        int indexOf(const PlayerPointContext::PlayerTuple& tuple);
        PlayerPointContext::PlayerTuple tupleAtIndex(const int &index) const;
        PlayerPointContext::PlayerTuple tupleAtId(const QUuid& id) const;
        PlayerPointContext::PlayerTuple tupleAtId(const PlayerTuples* _tuples, const QUuid& id);
        PlayerTuples createInitializedTuples();
        void replaceTupleAt(const int &index,const PlayerPointContext::PlayerTuple &tuple);
        int count() const;
        int _initialScore;
        PlayerTuples _playerTuples;
        QUuid _winner;
    };
}

#endif // DARTSPLAYERPOINTSERVICE_H
