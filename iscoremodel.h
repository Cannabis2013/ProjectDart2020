#ifndef ISCOREMODEL_H
#define ISCOREMODEL_H

#include "modelinterface.h"

template <class TUuid>
class IScore : public ModelInterface<TUuid>
{
public:
    virtual int point() const = 0;
    virtual IScore* setPoint(const int &point) = 0;

    virtual int score() const = 0;
    virtual IScore* setScore(const int &score) = 0;

    virtual int throwIndex() const = 0;
    virtual IScore* setThrowIndex(const int &index) = 0;

    virtual TUuid player() const = 0;
    virtual IScore* setPlayer(const TUuid &id) = 0;

    virtual int hint() const = 0;
    virtual IScore* setHint(const int &hint) = 0;

    virtual int keyCode() const = 0;
    virtual IScore* setKeyCode(const int &key) = 0;

    virtual int roundIndex() const = 0;
    virtual IScore* setRoundIndex(const int &index) = 0;

    virtual int setIndex() const = 0;
    virtual IScore* setSetIndex(const int &index) = 0;
};

#endif // ISCOREMODEL_H
