#ifndef SERVICECOLLECTION_H
#define SERVICECOLLECTION_H

class IServiceInitializer;
class IScoresReport;
class IMessagesReport;
class IStatusReport;
class IStatsReport;
class IDartsFinishes;
class ITurnController;
class ServiceInitializer;
class IDartsInputAdder;
class IDartsStatus;
class IDartsPlayers;
class IDartsJsonReport;
class IDartsInputs;
class IDartsScores;
class IDartsIndexes;
class IScoresCalculator;
class AbstractDartsEvaluator;
class DartsEvaluators;
class IDartsInputTrimmer;

class ServiceCollection {
public:
        DartsEvaluators* evaluators;
        IServiceInitializer* initializer;
        AbstractDartsEvaluator* evaluator;
        IScoresCalculator* calculator;
        IDartsIndexes* indexes;
        IDartsScores* scores;
        IDartsInputs* inputs;
        IDartsJsonReport* turnReport;
        IDartsPlayers* players;
        IDartsStatus* status;
        IDartsInputAdder* adder;
        IDartsInputTrimmer* trimmer;
        IDartsFinishes* finishes;
        ITurnController* turnController;
        IStatsReport* statsReport;
        IStatusReport* statusReport;
        IMessagesReport* messagesReport;
        IScoresReport* scoresReport;
};

#endif // SERVICECOLLECTION_H
