#ifndef DARTINPUTEVALUATOR_H
#define DARTINPUTEVALUATOR_H

#include "iclosurefilter.h"
#include <QStringList>

class ServiceCollection;
class IOpeningFilter;
class IScoresCalculator;
class IDartsStatus;
class IDartsPlayers;
class IDartsScores;

class DartsCloseningFilter : public IClosureFilter {
public:
    DartsCloseningFilter(ServiceCollection* services);
    void initFromFile() override;
    void saveState() override;
    void init(bool enabled) override;
    const QList<InputCandidate> filter(const QList<InputCandidate> &inputs) override;
    void evaluateWinnerCondition() override;

private:
    bool _enabled;
    // Services
    ServiceCollection* const _services;
};

#endif // DARTINPUTEVALUATOR_H
