#ifndef USERSCORESCONTROLLERINTERFACE_H
#define USERSCORESCONTROLLERINTERFACE_H

#include <quuid.h>
#include <qpair.h>
#include <qvector.h>

class IScoreController
{
public:
    virtual QUuid winnerId() const = 0;
    virtual IScoreController* setWinner(const QUuid& id) = 0;
    virtual QString winnerUserName() const = 0;

    virtual void addPlayerEntity(const QUuid&,const QString&) = 0;
    virtual void subtractPlayerScore(const QUuid&, const int&) = 0;
    virtual void addPlayerScore(const QUuid&, const int&) = 0;

    virtual int userScore(const int& index) const = 0;
    virtual int userScore(const QUuid&) const = 0;
    virtual void setUserScoreAtIndex(const int &index, const int &input) = 0;
    virtual void setUserScoresFromList(const QVector<int>& list) = 0;
    virtual void setUserScoreAtId(const QUuid &id, const int &input) = 0;

    virtual QString userNameAtIndex(const int &index) const = 0;
    virtual QString userNameFromId(const QUuid& id) const = 0;
    virtual QVector<QString> userNames() const = 0;
    virtual QUuid userIdAtIndex(const int &index) const = 0;

    virtual int playersCount() const = 0;
    virtual int initialScore() const = 0;
    virtual int calculateAccumulatedScoreCandidate(const int& index, const int& score) const = 0;
    virtual void resetScores() = 0;
};

#endif // USERSCORESCONTROLLERINTERFACE_H
