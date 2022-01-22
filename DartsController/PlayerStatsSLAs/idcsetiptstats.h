#ifndef IDCSETIPTSTATS_H
#define IDCSETIPTSTATS_H
struct DCIndex;
struct DCInput;
class IDCStatistics;
class IDCSetIptStats
{
public:
    virtual void set(DCInput &input, const DCIndex &idx, const int &initRemScore, IDCStatistics *statsContext) const = 0;
};
#endif // IDCDETSCORERANGE_H
