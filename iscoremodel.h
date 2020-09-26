#ifndef ISCOREMODEL_H
#define ISCOREMODEL_H

#include "isetmodel.h"

template <class TUuid>
class IScore : public IModel<TUuid>
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
};

#endif // ISCOREMODEL_H
