#ifndef IMODEL_H
#define IMODEL_H

template<class TUuid>
class IModel
{
public:
    virtual TUuid id() const = 0;
    virtual void setId(const TUuid &val) = 0;

    virtual int type() const = 0;
    virtual void setType(const int &val) = 0;

    virtual void setParent(const TUuid &parent) = 0;
    virtual TUuid parent() const = 0;
};

#endif // IMODEL_H
