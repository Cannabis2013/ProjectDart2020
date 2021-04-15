#ifndef ISCOREMODEL_H
#define ISCOREMODEL_H

#include "iscore.h"

template <class TUuid>
class IFtpScore : public IScore<TUuid>
{
public:
    virtual int point() const = 0;
    virtual IFtpScore* setPointValue(const int&) = 0;

    virtual int score() const = 0;
    virtual IFtpScore* setScoreValue(const int&) = 0;

    virtual int accumulatedScore() const = 0;
    virtual IFtpScore* setAccumulatedScore(const int&) = 0;

    virtual int attempt() const = 0;
    virtual IFtpScore* setAttempt(const int &index) = 0;

    virtual int roundIndex() const = 0;
    virtual IFtpScore* setRoundIndex(const int &index) = 0;

    virtual int setIndex() const = 0;
    virtual IFtpScore* setSetIndex(const int &index) = 0;
};

#endif // ISCOREMODEL_H
