#ifndef DARTINPUTEVALUATOR_H
#define DARTINPUTEVALUATOR_H

#include "abstractdartsevaluator.h"

class IPlayerAllowances;
class IScoresCalculator;
class IDartsStatus;
class IDartsPlayers;
class IDartsScores;

class DartsProfessionalEvaluator : public AbstractDartsEvaluator {
public:
        DartsProfessionalEvaluator(IDartsScores* scores,
            IDartsPlayers* players,
            IDartsStatus* status,
            IScoresCalculator* calculator);
        void init() override;
        bool evaluateInput(const QString& mod, const int& point) override;
        void evaluateWinnerCondition() override;
        void updateAllowance(const QString& name, const bool& allowance) override;

private:
        // Private member methods
        bool validateInput(const QString& name, const QString& mod, const int& point);
        bool validateRemaining(const QString& mod, const int& point, const int& current);

        // Services
        IDartsScores* const _scores;
        IDartsPlayers* const _players;
        IDartsStatus* const _status;
        IScoresCalculator* const _calculator;

        // Data storage
        IPlayerAllowances* _allowances;
};

#endif // DARTINPUTEVALUATOR_H
