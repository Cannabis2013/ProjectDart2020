#ifndef ISCOREMODEL_H
#define ISCOREMODEL_H

#include "isetmodel.h"

template <class TUuid>
class IScore : public IModel<TUuid>
{
public:
    virtual int point() const = 0;
    virtual void setPoint(const int &point) = 0;

    virtual int score() const = 0;
    virtual void setScore(const int &score) = 0;

    virtual int throwIndex() const = 0;
    virtual void setLegIndex(const int &index) = 0;

    virtual TUuid player() const = 0;
    virtual void setPlayer(const TUuid &id) = 0;

    virtual int hint() const = 0;
    virtual void setHint(const int &hint) = 0;
};

#endif // ISCOREMODEL_H
