#ifndef JSONTOSTATSMODEL_H
#define JSONTOSTATSMODEL_H
#include "Players/ijsontostatsmodel.h"
struct CurrentStat;
class JsonToStatsModel : public IJsonToStatsModel<CurrentStat>
{
public:
    virtual CurrentStat convert(const Json &json) const override;
};
#endif // JSONTOMIRROR_H
