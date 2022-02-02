#ifndef IDCUPDATESCORERANGE_H
#define IDCUPDATESCORERANGE_H
class DCStatsModel;
struct DCIndex;
struct DCInput;
class IDCStatistics;
class IDCUpdateScoreRange
{
public:
    virtual void update(DCInput &input) const = 0;
};
#endif // IDCDETSCORERANGE_H
