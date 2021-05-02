#ifndef ISCOREMODEL_H
#define ISCOREMODEL_H

#include "iscore.h"

template <class TUuid>
class IDartsScore : public IScore<TUuid>
{
public:
    virtual int point() const = 0;
    virtual IDartsScore* setPointValue(const int&) = 0;

    virtual int score() const = 0;
    virtual IDartsScore* setScoreValue(const int&) = 0;

    virtual int accumulatedScore() const = 0;
    virtual IDartsScore* setAccumulatedScore(const int&) = 0;

    virtual int attempt() const = 0;
    virtual IDartsScore* setAttempt(const int &index) = 0;

    virtual int roundIndex() const = 0;
    virtual IDartsScore* setRoundIndex(const int &index) = 0;

    virtual int setIndex() const = 0;
    virtual IDartsScore* setSetIndex(const int &index) = 0;
};

#endif // ISCOREMODEL_H
