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
        bool evaluateInput(const QString& mod, const int& point) override;
        void evaluateWinnerCondition() override;
        void updateAllowance(const QString& name, const bool& allowance) override;

private:
        // Private member methods
        bool validateInput(const QString& name, const QString& mod, const int& point);
        bool validateRemaining(const QString& mod, const int& point, const int& current);
        bool isValid(const int& point, const QString& mod) const;

        const QStringList AllowedMods = std::initializer_list<QString>({ "S", "D", "T" });
        const int MaxPoint = 60;

        // Services
        ServiceCollection* const _services;
        // Data storage
        IPlayerAllowances* _allowances;
};

#endif // DARTINPUTEVALUATOR_H
