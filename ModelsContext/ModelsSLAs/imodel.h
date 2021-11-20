#ifndef MODELINTERFACE_H
#define MODELINTERFACE_H
template<class TUuid>
class IModel
{
public:
    virtual TUuid id() const = 0;
    virtual void setId(const TUuid &val) = 0;
};

#endif // MODELINTERFACE_H
