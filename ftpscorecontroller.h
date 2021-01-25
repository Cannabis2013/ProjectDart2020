#ifndef FTPSCORECONTROLLER_H
#define FTPSCORECONTROLLER_H

#include "userscorescontrollerinterface.h"
#include <qlist.h>

#define INCONSISTENCY_EXCEPTION_MESSAGE "User inconsistency!"

template<class T1, class T2, class T3>
struct Tuple
{
    Tuple(T1 firstArg, T2 secondArg, T3 thirdArg)
    {
        first = firstArg;
        second = secondArg;
        third = thirdArg;
    }
    Tuple(){}

    bool operator==(const Tuple& other){
        if(other.first != this->first)
            return false;
        else if(other.second != this->second)
            return false;
        else if(other.third != this->third)
            return false;
        return true;
    }
    T1 first;
    T2 second;
    T3 third;
};
// S = {UserId, UserName, UserScore}
typedef Tuple<QUuid,QString,int> PlayerTuple;
typedef QList<PlayerTuple> PlayerTuples;
typedef QPair<QUuid,QString> PlayerPair;
typedef QList<PlayerPair> PlayerPairs;

typedef UserScoresControllerInterface<QUuid,QString,QVector<int>,QVector<QString>> ScoreControllerInterface;

class FTPScoreController : public ScoreControllerInterface
{
public:
    static FTPScoreController* createInstance(const QVector<QUuid>& userIds,
                                              const QVector<QString>& userNames,
                                              const QVector<int>& userScores,
                                              const int& initialScore,
                                              const QUuid &winner);
    // UserScoresControllerInterface interface
    int userscoreAtIndex(const int &index) const override;
    void setUserScoreAtIndex(const int &index, const int &input) override;
    void setUserScoresFromList(const QVector<int> &list) override;
    void setUserScoreAtId(const QUuid &id, const int &input) override;
    QString userNameAtIndex(const int &index) const override;
    QString userNameFromId(const QUuid &id) const override;
    QVector<QString> userNames() const override;
    QUuid userIdAtIndex(const int &index) const override;
    int playersCount() const override;
    QUuid winnerId() const override;
    ScoreControllerInterface *setWinner(const QUuid &id) override;
    QString winnerUserName() const override;
    int initialScore() const override;
    int calculateAggregateduserScoreCandidate(const int& index,
                                              const int& score) const override;
    void resetScores() override;

private:
    /*
     * Private constructor
     */

    FTPScoreController(const QVector<QUuid>& userIds,
                       const QVector<QString>& userNames,
                       const QVector<int>& userScores,
                       const int& initialScore,
                       const QUuid& winner);

    PlayerTuples assembleScoreTubble(const QVector<QUuid>& userIds,
                             const QVector<QString>& userNames,
                             const QVector<int>& userScores);

    PlayerTuple tupleAtIndex(const int &index) const;
    PlayerTuple tupleAtId(const QUuid& id) const;

    int indexOf(const PlayerTuple& tuple);

    void replaceTupleAt(const int &index,const PlayerTuple &tuple);
    int count() const;
    int _initialScore;
    PlayerTuples _playerTuples;
    QUuid _winner;
};

#endif // FTPSCORECONTROLLER_H
