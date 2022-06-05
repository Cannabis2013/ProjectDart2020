#ifndef REMOVEINPUTFROMCONTEXT_H
#define REMOVEINPUTFROMCONTEXT_H

#include <DartsStatistics/InputRoutines/IRemoveInputFromDb.h>

template<typename T> class ICreateStatModel;
struct CurrentStat;
struct SnapShot;
class IMirrorsDb;
template<typename T> class IStatsDb;
class ServicesContext;

class RemoveInputFromContext : public IRemoveInputFromDb
{
public:
        typedef IStatsDb<CurrentStat> StatsDb;
        typedef IStatsDb<SnapShot> InputsDb;
        RemoveInputFromContext(ServicesContext *provider);
        virtual bool remove(const QString &name) override;
private:
        SnapShot getInputByN(const QString &name, const int &n);
        StatsDb *_mirrorsDb;
        InputsDb *_iptsDb;
        ICreateStatModel<CurrentStat> *_createMirror;
};

#endif // REMOVEINPUTFROMCONTEXT_H
