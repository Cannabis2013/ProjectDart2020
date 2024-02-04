#ifndef CONTROLLERSERVICES_H
#define CONTROLLERSERVICES_H

#include "src/DartsController/Finishes/idartsfinishes.h"
#include "src/DartsController/controller/controllerinitializer.h"
#include "src/DartsController/controller/idartsturns.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/idartsinputs.h"
#include "src/DartsController/input/idartsinputadder.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/responses/idartsjsonreport.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/statistics/idartsstatistics.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/validation/abstractdartsevaluator.h"
#include "src/DartsController/validation/dartsevaluators.h"

class ControllerServices {
public:
        AbstractDartsEvaluator* evaluator() const;
        void setEvaluator(AbstractDartsEvaluator* newEvaluator);
        IDartsIndexes* indexes() const;
        void setIndexes(IDartsIndexes* newIndexes);
        IDartsScores* scores() const;
        void setScores(IDartsScores* newScores);
        IDartsInputs* inputs() const;
        void setInputs(IDartsInputs* newInputs);
        IDartsJsonReport* turnDetails() const;
        void setTurnInfo(IDartsJsonReport* newTurnValues);
        IDartsPlayers* players() const;
        void setPlayers(IDartsPlayers* newPlayers);
        IDartsStatistics* statistics() const;
        void setStatistics(IDartsStatistics* newStatistics);
        IDartsFinishes* finishes() const;
        void setFinishes(IDartsFinishes* newFinishes);
        IDartsStatus* status() const;
        void setStatus(IDartsStatus* newStatus);
        IDartsInputAdder* adder() const;
        void setAdder(IDartsInputAdder* newAdder);
        DartsEvaluators* evaluators() const;
        void setEvaluators(DartsEvaluators* newEvaluators);
        ControllerInitializer* initializer() const;
        void setInitializer(ControllerInitializer* newInitializor);
        IDartsTurns* turns() const;
        void setTurns(IDartsTurns* newTurns);

private:
        // Services
        AbstractDartsEvaluator* _evaluator = nullptr;
        IDartsIndexes* _indexes = nullptr;
        IDartsScores* _scores = nullptr;
        IDartsInputs* _inputs = nullptr;
        IDartsJsonReport* _turnInfo = nullptr;
        IDartsPlayers* _players = nullptr;
        IDartsStatistics* _statistics = nullptr;
        IDartsFinishes* _finishes = nullptr;
        IDartsStatus* _status = nullptr;
        IDartsInputAdder* _adder = nullptr;
        DartsEvaluators* _evaluators = nullptr;
        ControllerInitializer* _initializer = nullptr;
        IDartsTurns* _turns = nullptr;
};

#endif // CONTROLLERSERVICES_H
