#ifndef CREATESTATSREPORT_H
#define CREATESTATSREPORT_H

#include <DartsStatistics/Report/icreatereport.h>

struct CurrentStat;
class IMirrorsDb;
template<typename T> class IStatsDb;
class ServicesContext;

class CreateStatsReport : public ICreateReport
{
public:
    typedef IStatsDb<CurrentStat> StatsDb;
    CreateStatsReport(ServicesContext *provider);
    virtual ByteArray create(const QString &name) const override;
private:
    ByteArray makeReport(const CurrentStat&stats) const;
    StatsDb *_statsDb;
};

#endif // CREATESTATSREPORT_H
