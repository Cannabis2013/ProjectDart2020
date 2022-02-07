#ifndef REMOVEINPUTFROMCONTEXT_H
#define REMOVEINPUTFROMCONTEXT_H
#include "InputRoutines/IRemoveInputFromDb.h"
struct Input;
struct CurrentStats;
template<typename T> class IStatsDb;
class ServicesContext;
class RemoveInputFromContext : public IRemoveInputFromDb
{
public:
    typedef IStatsDb<CurrentStats> StatsDb;
    typedef IStatsDb<Input> InputsDb;
    RemoveInputFromContext(ServicesContext *provider);
    virtual bool remove(const QString &name) override;
private:
    Input getLastInput(const QString &name, const CurrentStats &stats);
    StatsDb *_statsDb;
    InputsDb *_iptsDb;
};

#endif // REMOVEINPUTFROMCONTEXT_H
