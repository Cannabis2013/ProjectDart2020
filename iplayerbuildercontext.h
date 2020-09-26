#ifndef IPLAYERBUILDERCONTEXT_H
#define IPLAYERBUILDERCONTEXT_H

template<class TString, class TUuid>
class IPlayerBuilderParameters
{
public:
    virtual TString playerName() const = 0;
    virtual TString eMail() const = 0;
    virtual TUuid id() const = 0;
    virtual int role() const = 0;
};

template<class TUuid>
class IPlayerModelOptions
{
public:
    virtual bool generateID() const = 0;
    virtual void enableGenerateUniqueID(const bool &enable) = 0;
};

#endif // IPLAYERBUILDERCONTEXT_H
