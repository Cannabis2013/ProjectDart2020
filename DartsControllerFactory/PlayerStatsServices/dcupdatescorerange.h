#ifndef DCUPDATESCORERANGE_H
#define DCUPDATESCORERANGE_H
#include "PlayerStatsSLAs/idcsetiptstats.h"
class DCServices;
class DCUpdateScoreRange : public IDCSetIptStats
{
public:
    DCUpdateScoreRange(DCServices *services);
    void update(DCInput &input) const override;
private:
    double middleValue(const DCIndex &index, const int &remainingScore, const int &initialScore) const;
    double toTwoDecimals(const double &value) const;
    void evaluateAndUpdateStats(DCStatsModel *stats, const int &score) const;
    void setInputRangeStats(DCInput &input, DCStatsModel *playerStat) const;
    DCServices *_services;
};
#endif // DSCUPDSCORERNG_H
