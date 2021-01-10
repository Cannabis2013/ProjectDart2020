#ifndef USERSCORESCONTROLLERINTERFACE_H
#define USERSCORESCONTROLLERINTERFACE_H

#include <quuid.h>
#include <qpair.h>

namespace UserScoresContext
{
    template<class T1, class T2, class T3>
    struct Tupple
    {
    public:
        Tupple(T1 firstArg, T2 secondArg, T3 thirdArg)
        {
            first = firstArg;
            second = secondArg;
            third = thirdArg;
        }
        T1 first;
        T2 second;
        T3 third;
    };

    typedef Tupple<QUuid,QString,int> PlayerTupple;
    typedef QList<PlayerTupple> PlayerTubbles;
    typedef QPair<QUuid,QString> PlayerPair;
    typedef QList<PlayerPair> PlayerPairs;
}

template<typename TUuid, typename TString, typename  TList>
class UserScoresControllerInterface
{
public:
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
