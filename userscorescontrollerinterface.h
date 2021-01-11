#ifndef USERSCORESCONTROLLERINTERFACE_H
#define USERSCORESCONTROLLERINTERFACE_H

#include <quuid.h>
#include <qpair.h>

template<typename TUuid, typename TString, typename  TList>
class UserScoresControllerInterface
{
public:
    virtual TUuid winner() const = 0;
    virtual UserScoresControllerInterface* setWinner(const QUuid& id) = 0;

    virtual int scoreAtIndex(const int &index) const = 0;
    virtual void setScoreAtIndex(const int &index, const int &input) = 0;
    virtual void setScoreFromList(const TList& list) = 0;
    virtual void setScoreAtId(const TUuid &id, const int &input) = 0;

    virtual TString userNameAtIndex(const int &index) const = 0;
    virtual TString userNameFromId(const TUuid& id) const = 0;
    virtual TUuid userIdAtIndex(const int &index) const = 0;

    virtual int userScoresCount() const = 0;
};

#endif // USERSCORESCONTROLLERINTERFACE_H
