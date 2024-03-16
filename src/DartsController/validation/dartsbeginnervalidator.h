#ifndef DARTSOVERTHROWEVALUATOR_H
#define DARTSOVERTHROWEVALUATOR_H

#include "abstractdartsevaluator.h"
#include <QStringList>

class ServiceCollection;
class IDartsStatus;
class IDartsPlayers;
class IDartsScores;

class DartsBeginnerValidator : public AbstractDartsEvaluator {
public:
        DartsBeginnerValidator(ServiceCollection* services);

        bool evaluateInput(const QString& mod, const int& point) override;
        void evaluateWinnerCondition() override;
private:
        bool isValid(const QString& mod, const int& point) const;

        // Services
        ServiceCollection* _services;

        // Member variables
        const QStringList AllowedMods = std::initializer_list<QString>({ "S", "D", "T" });
        const int MaxPoint = 60;
};

#endif // DARTSOVERTHROWEVALUATOR_H
