#ifndef IMODEL_H
#define IMODEL_H

#include <quuid.h>
#include <qstring.h>

class IPlayer
{
public:
    typedef QString String;
    typedef QUuid Id;
    virtual Id id() const = 0;
    virtual void setId(const Id &val) = 0;
    virtual String name() const = 0;
    virtual IPlayer* setName(const String &name) = 0;
    virtual String mail() const = 0;
    virtual IPlayer* setEmail(const String& email) = 0;
    virtual bool operator==(IPlayer* &other) = 0;
};
#endif // IMODEL_H
