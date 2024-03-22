#ifndef STATSCALCULATOR_H
#define STATSCALCULATOR_H

#include "istatscalculator.h"
#include "src/input/models/input.h"

class ServiceCollection;

#define USE_POOR_AVERAGE

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
