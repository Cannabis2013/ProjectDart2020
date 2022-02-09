#ifndef JSONTOSTATSMODEL_H
#define JSONTOSTATSMODEL_H
#include "Players/ijsontoplayer.h"
struct CurrentStat;
class JsonToStatsModel : public IJsonToPlayer<CurrentStat>
{
public:
    virtual CurrentStat create(const Json &json) const override;
};
#endif // JSONTOMIRROR_H
