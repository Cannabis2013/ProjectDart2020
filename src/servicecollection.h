#ifndef SERVICECOLLECTION_H
#define SERVICECOLLECTION_H

class IValidationOpenPersistence;
class IOpenValidator;
class IDartsInputsUpdater;
class IStatsCalculator;
class IDartsInputsFilter;
class IDartsScoresFetch;
class IServiceInitializer;
class IScoresReport;
class IMessagesReport;
class IStatsReport;
class IDartsFinishes;
class ITurnController;
class DartsInitializer;
class IDartsInputController;
class IDartsStatus;
class IDartsPlayers;
class IDartsJsonReport;
class IDartsInputs;
class IDartsRemainings;
class IDartsIndexes;
class IClosureFilter;

class ServiceCollection {
public:
        IServiceInitializer* initializer;
        IClosureFilter* closeningFilter;
        IOpenValidator* openingFilter;
        IDartsIndexes* indexes;
        IDartsRemainings* scores;
        IDartsInputs* inputs;
        IDartsJsonReport* turnReport;
        IDartsPlayers* players;
        IDartsStatus* status;
        IDartsInputController* adder;
        ITurnController* turnController;
        IStatsReport* statsReport;
        IMessagesReport* messagesReport;
        IScoresReport* scoresReport;
        IDartsInputsFilter* inputsFilter;
        IStatsCalculator* inputStatistics;
        IDartsInputsUpdater* inputsUpdater;
};

#endif // SERVICECOLLECTION_H
