#ifndef CREATESTATSREPORT_H
#define CREATESTATSREPORT_H
#include "Report/icreatereport.h"
class CurrentStats;
template<typename T> class IStatsDb;
class ServicesContext;
class CreateStatsReport : public ICreateReport
{
public:
    typedef IStatsDb<CurrentStats> StatsDb;
    CreateStatsReport(ServicesContext *provider);
    virtual ByteArray create(const QString &name) const override;
private:
    ByteArray makeReport(const CurrentStats &stats) const;
    StatsDb *_statsDb;
};

#endif // CREATESTATSREPORT_H
