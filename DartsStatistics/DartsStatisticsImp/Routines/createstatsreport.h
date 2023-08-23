#ifndef CREATESTATSREPORT_H
#define CREATESTATSREPORT_H

#include <DartsStatistics/Contracts/Report/icreatereport.h>

struct PlayerStats;
class IMirrorsDb;
template<typename T> class IStatsDb;
class ServicesContext;

class CreateStatsReport : public ICreateReport
{
public:
        typedef IStatsDb<PlayerStats> StatsDb;
    CreateStatsReport(ServicesContext *provider);
    virtual ByteArray create(const QString &name) const override;
private:
    ByteArray makeReport(const PlayerStats&stats) const;
    StatsDb *_statsDb;
};

#endif // CREATESTATSREPORT_H
