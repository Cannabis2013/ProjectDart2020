#ifndef USERSCORESCONTROLLERINTERFACE_H
#define USERSCORESCONTROLLERINTERFACE_H

#include <quuid.h>
#include <qpair.h>

template<typename TUuid,
         typename TString,
         typename  TScoreList,
         typename TUserNameList>
class IScoreController
{
public:
    virtual TUuid winnerId() const = 0;
    virtual IScoreController* setWinner(const QUuid& id) = 0;
    virtual TString winnerUserName() const = 0;

    virtual void addPlayerEntity(const TUuid&,const TString&) = 0;
    virtual void subtractPlayerScore(const TUuid&, const int&) = 0;
    virtual void addPlayerScore(const QUuid&, const int&) = 0;

    virtual int userScore(const int& index) const = 0;
    virtual int userScore(const TUuid&) const = 0;
    virtual void setUserScoreAtIndex(const int &index, const int &input) = 0;
    virtual void setUserScoresFromList(const TScoreList& list) = 0;
    virtual void setUserScoreAtId(const TUuid &id, const int &input) = 0;

    virtual TString userNameAtIndex(const int &index) const = 0;
    virtual TString userNameFromId(const TUuid& id) const = 0;
    virtual TUserNameList userNames() const = 0;
    virtual TUuid userIdAtIndex(const int &index) const = 0;

    virtual int playersCount() const = 0;
    virtual int initialScore() const = 0;
    virtual int calculateAccumulatedScoreCandidate(const int& index, const int& score) const = 0;
    virtual void resetScores() = 0;
};

#endif // USERSCORESCONTROLLERINTERFACE_H
