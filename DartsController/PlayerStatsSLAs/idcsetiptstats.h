#ifndef IDCSETIPTSTATS_H
#define IDCSETIPTSTATS_H
class DCStatsModel;
struct DCIndex;
struct DCInput;
class IDCStatistics;
class IDCSetIptStats
{
public:
    virtual void update(DCInput &input) const = 0;
};
#endif // IDCDETSCORERANGE_H
