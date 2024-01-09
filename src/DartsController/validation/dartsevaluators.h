#ifndef DARTSEVALUATORS_H
#define DARTSEVALUATORS_H

#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/scores/iscorescalculator.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/validation/abstractdartsevaluator.h"

class DartsEvaluators {
public:
        DartsEvaluators(IDartsScores* scores,
            IDartsPlayers* players,
            IDartsStatus* status,
            IScoresCalculator* calculator);

        AbstractDartsEvaluator* validator();
        AbstractDartsEvaluator* validator(const int& mode);

        bool readFromFile();
        void saveState();

private:
        AbstractDartsEvaluator* fromMode();

        // Services
        IDartsScores* const _scores;
        IDartsPlayers* const _players;
        IDartsStatus* const _status;
        IScoresCalculator* const _calculator;

        // Member variables
        int _mode = 0;
};

#endif // DARTSEVALUATORS_H
