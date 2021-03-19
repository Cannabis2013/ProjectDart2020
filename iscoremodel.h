#ifndef ISCOREMODEL_H
#define ISCOREMODEL_H

#include "imodel.h"

template <class TUuid>
class IScore : public IModel<TUuid>
{
public:
    virtual int point() const = 0;
    virtual IScore* setPointValue(const int &point) = 0;

    virtual int score() const = 0;
    virtual IScore* setScoreValue(const int &score) = 0;

    virtual int attempt() const = 0;
    virtual IScore* setAttempt(const int &index) = 0;

    virtual TUuid player() const = 0;
    virtual IScore* setPlayer(const TUuid &id) = 0;

    virtual int hint() const = 0;
    virtual IScore* setDisplayHint(const int &hint) = 0;

    virtual int keyCode() const = 0;
    virtual IScore* setKeyCode(const int &key) = 0;

    virtual int roundIndex() const = 0;
    virtual IScore* setRoundIndex(const int &index) = 0;

    virtual int setIndex() const = 0;
    virtual IScore* setSetIndex(const int &index) = 0;
};

#endif // ISCOREMODEL_H
