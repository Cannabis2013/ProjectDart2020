#ifndef STATSCALCULATOR_H
#define STATSCALCULATOR_H

#include "istatscalculator.h"
#include "src/DartsController/input/models/Input.h"

class ServiceCollection;

class StatsCalculator : public IStatsCalculator {
public:
        StatsCalculator(ServiceCollection* services);

        double middle(const QString& name) const override;
        int lowest(const QString& name) const override;
        int highest(const QString& name) const override;

private:
        ServiceCollection* _services;
};

#endif // STATSCALCULATOR_H
