#ifndef STATSCALCULATOR_H
#define STATSCALCULATOR_H

#include "istatscalculator.h"

#define USE_IMP_1

class ServiceCollection;

class StatsCalculator : public IStatsCalculator {
public:
    StatsCalculator(ServiceCollection* services);
    double middle(const QString& name) const override;
    int lowest(const QString& name) const override;
    int highest(const QString& name) const override;

private:
    int finishedRounds(const int& playerIndex) const;
    int playerScore(const QString& name) const;
    ServiceCollection* _services;
};

#endif // STATSCALCULATOR_H
