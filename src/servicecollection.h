#ifndef SERVICECOLLECTION_H
#define SERVICECOLLECTION_H

class IOpeningFilter;
class IScoresDelta;
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
class DartsInitializer;
class IDartsInputController;
class IDartsStatus;
class IDartsPlayers;
class IDartsJsonReport;
class IDartsInputs;
class IDartsScores;
class IDartsIndexes;
class IScoresCalculator;
class IClosureFilter;

class ServiceCollection {
public:
        IServiceInitializer* initializer;
        IClosureFilter* closeningFilter;
        IOpeningFilter* openingFilter;
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
        IDartsInputsFilter* inputsFilter;
        IStatsCalculator* inputStatistics;
        IPlayerFetcher* playerFetcher;
        IDartsInputsUpdater* inputsUpdater;
        IScoresDelta* scoresDelta;
};

#endif // SERVICECOLLECTION_H
