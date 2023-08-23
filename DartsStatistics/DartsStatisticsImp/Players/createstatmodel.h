#ifndef CREATESTATMODEL_H
#define CREATESTATMODEL_H

#include <DartsStatistics/Contracts/Players/ICreateStatModel.h>

struct PlayerStats;
class CreateStatModel : public ICreateStatModel<PlayerStats>
{
public:
        virtual PlayerStats create(const QString &name) const override;
};

#endif // CREATESTATMODEL_H
