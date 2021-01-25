#ifndef USERSCORESCONTROLLERINTERFACE_H
#define USERSCORESCONTROLLERINTERFACE_H

#include <quuid.h>
#include <qpair.h>

template<typename TUuid, typename TString, typename  TScoreList, typename TUserNameList>
class UserScoresControllerInterface
{
public:
    virtual TUuid winnerId() const = 0;
    virtual UserScoresControllerInterface* setWinner(const QUuid& id) = 0;
    virtual TString winnerUserName() const = 0;

    virtual int userscoreAtIndex(const int &index) const = 0;
    virtual void setUserScoreAtIndex(const int &index, const int &input) = 0;
    virtual void setUserScoresFromList(const TScoreList& list) = 0;
    virtual void setUserScoreAtId(const TUuid &id, const int &input) = 0;

    virtual TString userNameAtIndex(const int &index) const = 0;
    virtual TString userNameFromId(const TUuid& id) const = 0;
    virtual TUserNameList userNames() const = 0;
    virtual TUuid userIdAtIndex(const int &index) const = 0;

    virtual int playersCount() const = 0;
    virtual int initialScore() const = 0;
    virtual int calculateAggregateduserScoreCandidate(const int& index, const int& score) const = 0;
    virtual void resetScores() = 0;
};

#endif // USERSCORESCONTROLLERINTERFACE_H
