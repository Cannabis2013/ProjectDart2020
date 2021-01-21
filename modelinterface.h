#ifndef MODELINTERFACE_H
#define MODELINTERFACE_H

template<class TUuid>
class ModelInterface
{
public:
    virtual TUuid id() const = 0;
    virtual ModelInterface* setId(const TUuid &val) = 0;

    virtual int type() const = 0;
    virtual ModelInterface* setType(const int &val) = 0;

    virtual ModelInterface* setParent(const TUuid &parent) = 0;
    virtual TUuid parent() const = 0;
};

#endif // MODELINTERFACE_H
