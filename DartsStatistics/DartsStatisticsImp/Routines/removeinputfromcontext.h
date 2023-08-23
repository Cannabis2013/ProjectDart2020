#ifndef REMOVEINPUTFROMCONTEXT_H
#define REMOVEINPUTFROMCONTEXT_H

#include <DartsStatistics/Contracts/InputRoutines/IRemoveInputFromDb.h>

template<typename T> class ICreateStatModel;
struct PlayerStats;
struct SnapShot;
class IMirrorsDb;
template<typename T> class IStatsDb;
class ServicesContext;

class RemoveInputFromContext : public IRemoveInputFromDb
{
public:
        typedef IStatsDb<PlayerStats> StatsDb;
        typedef IStatsDb<SnapShot> InputsDb;
        RemoveInputFromContext(ServicesContext *provider);
        virtual bool remove(const QString &name) override;
private:
        SnapShot getInputByN(const QString &name, const int &n);
        StatsDb *_mirrorsDb;
        InputsDb *_iptsDb;
        ICreateStatModel<PlayerStats> *_createMirror;
};

#endif // REMOVEINPUTFROMCONTEXT_H
