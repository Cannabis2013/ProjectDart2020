#ifndef IPLAYERBUILDERCONTEXT_H
#define IPLAYERBUILDERCONTEXT_H

class IPlayerBuilderConfiguration
{
public:
    virtual bool generateUniqueID() const = 0;
};

template<class TString, class TUuid>
class IPlayerBuilderParameters
{
public:
    virtual TString playerName() const = 0;
    virtual TString eMail() const = 0;
    virtual TUuid id() const = 0;
    virtual int role() const = 0;
};

#endif // IPLAYERBUILDERCONTEXT_H
