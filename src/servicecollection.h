#ifndef SERVICECOLLECTION_H
#define SERVICECOLLECTION_H

class IValidationOpenPersistence;
class IOpenValidator;
class IDartsInputsUpdater;
class IPlayerFetcher;
class IStatsCalculator;
class IDartsInputsFilter;
class IDartsScoresFetch;
class IServiceInitializer;
class IScoresReport;
class IMessagesReport;
class IPlayerReport;
class IStatsReport;
class IDartsFinishes;
class ITurnController;
class DartsInitializer;
class IDartsInputController;
class IDartsStatus;
class IDartsPlayers;
class IDartsJsonReport;
class IDartsInputs;
class IDartsScores;
class IDartsIndexes;
class IClosureFilter;

class ServiceCollection {
public:
        IServiceInitializer* initializer;
        IClosureFilter* closeningFilter;
        IOpenValidator* openingFilter;
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
        IDartsInputsFilter* inputsFilter;
        IStatsCalculator* inputStatistics;
        IPlayerFetcher* playerFetcher;
        IDartsInputsUpdater* inputsUpdater;
        IValidationOpenPersistence* openPersistence;
};

#endif // SERVICECOLLECTION_H
