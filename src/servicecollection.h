#ifndef SERVICECOLLECTION_H
#define SERVICECOLLECTION_H

class IDartsInputsUpdater;
class IPlayerFetcher;
class IStatsCalculator;
class IDartsInputsFilter;
class IDartsScoresFetch;
class IScoresUpdate;
class IServiceInitializer;
class IScoresReport;
class IMessagesReport;
class IPlayerReport;
class IStatsReport;
class IDartsFinishes;
class ITurnController;
class ServiceInitializer;
class IDartsInputController;
class IDartsStatus;
class IDartsPlayers;
class IDartsJsonReport;
class IDartsInputs;
class IDartsScores;
class IDartsIndexes;
class IScoresCalculator;
class AbstractDartsEvaluator;
class DartsEvaluators;

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
        IDartsInputController* adder;
        IDartsFinishes* finishes;
        ITurnController* turnController;
        IStatsReport* statsReport;
        IPlayerReport* statusReport;
        IMessagesReport* messagesReport;
        IScoresReport* scoresReport;
        IScoresUpdate* scoresUpdate;
        IDartsScoresFetch* scoresFetcher;
        IDartsInputsFilter* inputsFilter;
        IStatsCalculator* inputStatistics;
        IPlayerFetcher* playerFetcher;
        IDartsInputsUpdater* inputsUpdater;
};

#endif // SERVICECOLLECTION_H
