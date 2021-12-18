#ifndef MODELINTERFACE_H
#define MODELINTERFACE_H
template<class TUuid>
class IModel
{
public:
    typedef TUuid Id;
    virtual Id id() const = 0;
    virtual void setId(const Id &val) = 0;
};

#endif // MODELINTERFACE_H
