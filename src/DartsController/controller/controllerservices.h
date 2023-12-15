#ifndef CONTROLLERSERVICES_H
#define CONTROLLERSERVICES_H

#include "src/DartsController/Finishes/idartsfinishes.h"
#include "src/DartsController/controller/controllerinitializer.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/input/idartsinputadder.h"
#include "src/DartsController/input/idartsinputtrimmer.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/responses/idartsinforesponse.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/statistics/idartsstatistics.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/validation/dartsevaluators.h"
#include "src/DartsController/validation/idartsevaluator.h"

class ControllerServices {
public:
        IDartsEvaluator* evaluator() const;
        void setEvaluator(IDartsEvaluator* newEvaluator);
        IDartsIndexes* indexes() const;
        void setIndexes(IDartsIndexes* newIndexes);
        IDartsScores* scores() const;
        void setScores(IDartsScores* newScores);
        IDartsInputs* inputs() const;
        void setInputs(IDartsInputs* newInputs);
        IDartsInfoResponse* turnValues() const;
        void setTurnValues(IDartsInfoResponse* newTurnValues);
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
        IDartsInputTrimmer* trimmer() const;
        void setTrimmer(IDartsInputTrimmer* newTrimmer);
        ControllerInitializer* initializer() const;
        void setInitializer(ControllerInitializer* newInitializor);

private:
        // Services
        IDartsEvaluator* _evaluator = nullptr;
        IDartsIndexes* _indexes = nullptr;
        IDartsScores* _scores = nullptr;
        IDartsInputs* _inputs = nullptr;
        IDartsInfoResponse* _turnValues = nullptr;
        IDartsPlayers* _players = nullptr;
        IDartsStatistics* _statistics = nullptr;
        IDartsFinishes* _finishes = nullptr;
        IDartsStatus* _status = nullptr;
        IDartsInputAdder* _adder = nullptr;
        DartsEvaluators* _evaluators = nullptr;
        IDartsInputTrimmer* _trimmer = nullptr;
        ControllerInitializer* _initializer = nullptr;
};

#endif // CONTROLLERSERVICES_H
