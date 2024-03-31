#ifndef STATSCALCULATOR_H
#define STATSCALCULATOR_H

#include "istatscalculator.h"
#include "src/input/models/dartsinput.h"

class ServiceCollection;

#define USE_IMP_2

class StatsCalculator : public IStatsCalculator {
public:
        StatsCalculator(ServiceCollection* services);

        double middle(const QString& name) const override;
        int lowest(const QString& name) const override;
        int highest(const QString& name) const override;

private:
        int finishedRounds() const;
        int playerScore(const QString& name) const;
        ServiceCollection* _services;
};

#endif // STATSCALCULATOR_H
