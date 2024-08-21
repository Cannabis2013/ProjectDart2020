#ifndef DARTINPUTEVALUATOR_H
#define DARTINPUTEVALUATOR_H

#include "abstractdartsevaluator.h"
#include <QStringList>

class ServiceCollection;
class IPlayerAllowances;
class IScoresCalculator;
class IDartsStatus;
class IDartsPlayers;
class IDartsScores;

class DartsProfessionalEvaluator : public AbstractDartsEvaluator {
public:
    DartsProfessionalEvaluator(ServiceCollection* services);
    void init() override;
    const QList<InputCandidate> acceptedInputs(const QList<InputCandidate> &candidates) override;
    void evaluateWinnerCondition() override;

private:
    // Private member methods
    Candidates validInputs(const Candidates &candidates, const QString& name);
    bool isValid(const int& point, const QString& mod) const;
    Candidates accepted(const Candidates &candidates);
    int currentRemaining() const;

    const QStringList AllowedMods = std::initializer_list<QString>({ "S", "D", "T" });
    const int MaxPoint = 60;

    // Services
    ServiceCollection* const _services;
    // Data storage
    IPlayerAllowances* _allowances;
};

#endif // DARTINPUTEVALUATOR_H
