#ifndef FTPSCORECONTROLLER_H
#define FTPSCORECONTROLLER_H

#include "iplayerscoreservice.h"
#include "dartsscore.h"
#include <qlist.h>

#define INCONSISTENCY_EXCEPTION_MESSAGE "User inconsistency!"

namespace DartsScoreMultiAttemptContext{
    namespace PlayerScoreContext
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

            bool operator==(const PlayerTuple& other){
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

    class DartsPlayerScoreService : public IPlayerScoreService<DartsScore>
    {
    public:
        // Tuple : {UserId, UserName, UserScore}
        typedef QVector<PlayerScoreContext::PlayerTuple> PlayerTuples;
        typedef QPair<QUuid,QString> PlayerPair;
        typedef QVector<PlayerPair> PlayerPairs;
        static DartsPlayerScoreService* createInstance(const int& initialScore,
                                                  const QUuid &winner);
        virtual void addPlayerEntity(const QUuid &id, const QString &name) override;
        virtual int subtractPlayerScoreByModel(const DartsScore *model) override;
        void subtractPlayerScoreByModels(const QVector<const DartsScore *> &models) override;
        virtual int addPlayerScore(const QUuid& id, const int &score) override;
        // UserScoresControllerInterface interface
        int playerScore(const int &index) const override;
        int playerScore(const QUuid& id) const override;
        void setPlayerScoreByIndex(const int &index, const int &input) override;
        void setPlayerScoresByList(const QVector<int> &list) override;
        void setPlayerScoreById(const QUuid &id, const int &input) override;
        QString playerNameByIndex(const int &index) const override;
        QString playerNameById(const QUuid &id) const override;
        QVector<QString> playerNames() const override;
        QUuid playerIdAtIndex(const int &index) const override;
        int playersCount() const override;
        QUuid winnerId() const override;
        IPlayerScoreService *setWinner(const QUuid &id) override;
        QString winnerUserName() const override;
        int initialScore() const override;
        int calculateAccumulatedScoreCandidate(const int& index,
                                               const int& score) const override;
        void resetScores() override;
    private:
        /*
         * Private constructor
         */
        DartsPlayerScoreService(const int& initialScore,
                           const QUuid& winner);
        PlayerTuples assembleScoreTubble(const QVector<QUuid>& userIds,
                                 const QVector<QString>& userNames,
                                 const QVector<int>& userScores);
        PlayerScoreContext::PlayerTuple tupleAtIndex(const int &index) const;
        PlayerScoreContext::PlayerTuple tupleAtId(const QUuid& id) const;
        PlayerScoreContext::PlayerTuple tupleAtId(const PlayerTuples* _tuples, const QUuid& id);
        PlayerTuples createInitializedTuples();

        int indexOf(const PlayerScoreContext::PlayerTuple& tuple);
        void replaceTupleAt(const int &index,const PlayerScoreContext::PlayerTuple &tuple);
        int count() const;
        int _initialScore;
        PlayerTuples _playerTuples;
        QUuid _winner;
    };
}


#endif // FTPSCORECONTROLLER_H
