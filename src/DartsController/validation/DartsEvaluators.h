#ifndef DARTSEVALUATORS_H
#define DARTSEVALUATORS_H

#include "src/DartsController/validation/dartsofficialvalidator.h"
#include "src/DartsController/validation/dartsoverthrowvalidator.h"
#include "src/DartsController/validation/idartsevaluator.h"

class DartsEvaluators {
public:
        DartsEvaluators(IDartsScores* scores, IDartsPlayers* players, IDartsStatus* status)
            : _scores(scores)
            , _players(players)
            , _status(status)
        {
        }

        IDartsEvaluator* validator(const int& mode)
        {
                if (mode == 0)
                        return new DartsOfficialValidator(_scores, _players, _status);
                else if (mode == 1)
                        return new DartsOverthrowValidator(_scores, _players, _status);
                return nullptr;
        }

private:
        // Services
        IDartsScores* const _scores;
        IDartsPlayers* const _players;
        IDartsStatus* const _status;
};

#endif // DARTSEVALUATORS_H
