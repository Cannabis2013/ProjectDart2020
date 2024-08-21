#ifndef DARTSMEDIUMVALIDATOR_H
#define DARTSMEDIUMVALIDATOR_H

#include "abstractdartsevaluator.h"
#include <QStringList>

class ServiceCollection;

class DartsMediumValidator : public AbstractDartsEvaluator
{
public:
    DartsMediumValidator(ServiceCollection *services);

    const QList<InputCandidate> acceptedInputs(const QList<InputCandidate> &candidates) override;
    void evaluateWinnerCondition() override;

private:
    Candidates validInputs(const Candidates &candidates) const;
    Candidates accepted(const Candidates &candidates);
    int currentRemaining() const;
    // Services
    ServiceCollection* _services;
    // Member variables
    const QStringList AllowedMods = std::initializer_list<QString>({ "S", "D", "T" });
    const int MaxPoint = 60;
};

#endif // DARTSMEDIUMVALIDATOR_H
