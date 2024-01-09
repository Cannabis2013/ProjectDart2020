#ifndef DARTINPUTEVALUATOR_H
#define DARTINPUTEVALUATOR_H

#include "abstractdartsevaluator.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/scores/iscorescalculator.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/validation/iplayerallowances.h"
#include <QPair>

using namespace std;

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
