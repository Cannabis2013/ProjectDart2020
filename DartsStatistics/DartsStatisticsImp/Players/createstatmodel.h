#ifndef CREATESTATMODEL_H
#define CREATESTATMODEL_H

#include <DartsStatistics/Contracts/Players/ICreateStatModel.h>

struct CurrentStat;
class CreateStatModel : public ICreateStatModel<CurrentStat>
{
public:
    virtual CurrentStat create(const QString &name) const override;
};

#endif // CREATESTATMODEL_H
