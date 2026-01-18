#ifndef DARTINPUTEVALUATOR_H
#define DARTINPUTEVALUATOR_H

#include "iclosurefilter.h"
#include <QStringList>

class ServiceCollection;
class IOpenValidator;
class IScoresCalculator;
class IDartsStatus;
class IDartsPlayers;
class IDartsRemainings;

class DartsCloseningFilter : public IClosureFilter {
  public:
    DartsCloseningFilter(ServiceCollection* services);
    void init(const QString& mod) override;
    void initFromFile() override;
    void saveState() override;
    const QList<InputCandidate> filter(const QList<InputCandidate> &inputs) override;

  private:
    bool _enabled;
    QString _mod;
    // Services
    ServiceCollection* const _services;
};

#endif // DARTINPUTEVALUATOR_H
