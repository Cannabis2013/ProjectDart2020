#ifndef IPLAYERBUILDERCONTEXT_H
#define IPLAYERBUILDERCONTEXT_H

class IPlayerBuilderConfiguration
{
public:
    virtual bool generateUniqueID() const = 0;
    virtual bool generateCustomID() const = 0;
};

template<class TString>
class IPlayerBuilderParameters
{
public:
    virtual TString firstName() const = 0;
    virtual TString lastName() const = 0;
    virtual TString eMail() const = 0;

    virtual int role() const = 0;
};

#endif // IPLAYERBUILDERCONTEXT_H
