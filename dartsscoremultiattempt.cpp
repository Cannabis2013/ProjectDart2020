#include "dartsscoremultiattempt.h"
namespace DartsScoreMultiAttemptContext {
    void DartsScoreMultiAttempt::start()
    {
        if(_currentStatus != ControllerState::Initialized &&
                _currentStatus != ControllerState::Stopped)
        {
            emit controllerIsNotInitialized();
            return;
        }
        setCurrentStatus(ControllerState::AwaitsInput);
        sendCurrentTurnValues();
    }

    void DartsScoreMultiAttempt::stop()
    {
        setCurrentStatus(ControllerState::Stopped);
        emit controllerIsStopped();
    }

    void DartsScoreMultiAttempt::handleAndProcessUserInput(const QByteArray& json)
    {
        auto score = _jsonService->getScoreByJson(json);
        auto setIndex = _indexController->setIndex();
        auto accumulatedScore = _scoreController->calculateAccumulatedScoreCandidate(setIndex,score);
        auto domain = _scoreEvaluator->validateInput(accumulatedScore);
        processDomain(domain,score);
    }

    void DartsScoreMultiAttempt::handleRequestForCurrentTournamentMetaData()
    {
        auto tournament = this->tournament();
        emit sendCurrentTournamentId(tournament);
    }

    void DartsScoreMultiAttempt::assembleMultiAttemptDartsScores()
    {
        auto json = _jsonService->assembleJsonDartsMultiAttemptScores(_scoreController);
        emit sendMultiAttemptDartsScores(json);
    }

    void DartsScoreMultiAttempt::handleRequestDartsScores()
    {
        auto tournamentId = tournament();
        emit requestDartsScores(tournamentId);
    }

    void DartsScoreMultiAttempt::handleScoreAddedToDataContext(const QByteArray &json)
    {
        auto dartsScore = DartsScore::fromJson(json);
        auto totalScore = _scoreController->subtractPlayerScoreByModel(dartsScore);
        _indexController->syncIndex();
        _addAccumulatedScoreToModel->service(dartsScore,totalScore);
        emit scoreAddedSuccess(dartsScore->toJson());
    }

    void DartsScoreMultiAttempt::handleResetTournament()
    {
        _currentStatus = ControllerState::resetState;
        _indexController->reset();
        _scoreController->resetScores();
        auto tournamentId = tournament();
        emit requestResetTournament(tournamentId);
    }

    void DartsScoreMultiAttempt::sendCurrentTurnValues()
    {
        auto model = _assembleDartsScoreTurnValues->service(_indexController,
                                                            _scoreController,
                                                            _scoreLogisticInterface);
        emit isReadyAndAwaitsInput(model->toJson());
    }

    QString DartsScoreMultiAttempt::currentActiveUser()
    {
        auto index = _indexController->setIndex();
        auto playerName = _scoreController->playerNameByIndex(index);
        return playerName;
    }

    QUuid DartsScoreMultiAttempt::currentActivePlayerId()
    {
        auto index = _indexController->setIndex();
        auto playerID = _scoreController->playerIdAtIndex(index);
        return playerID;
    }

    QUuid DartsScoreMultiAttempt::tournament()
    {
        return _tournament;
    }

    int DartsScoreMultiAttempt::status()
    {
        return _currentStatus;
    }

    int DartsScoreMultiAttempt::lastPlayerIndex()
    {
        auto playerCount = _scoreController->playersCount();
        auto lastIndex = playerCount - 1;
        return lastIndex;
    }


    QUuid DartsScoreMultiAttempt::undoTurn()
    {
        if(status() == ControllerState::WinnerDeclared)
            return QUuid();
        _currentStatus = ControllerState::UndoState;
        _indexController->undo();
        auto roundIndex = _indexController->roundIndex();
        emit hideDartsScore(tournament(),
                            currentActivePlayerId(),
                            roundIndex);
        auto playerId = currentActivePlayerId();
        return playerId;
    }

    QUuid DartsScoreMultiAttempt::redoTurn()
    {
        setCurrentStatus(ControllerState::RedoState);
        auto activeUser = currentActivePlayerId();
        auto roundIndex = _indexController->roundIndex();
        _indexController->redo();
        emit revealDartsScore(tournament(),
                              activeUser,
                              roundIndex);
        auto index = _indexController->setIndex();
        auto playerId = _scoreController->playerIdAtIndex(index);
        return playerId;
    }

    void DartsScoreMultiAttempt::addPoint(const int& score)
    {
        if(currentStatus() != ControllerState::WinnerDeclared)
            setCurrentStatus(ControllerState::AddScoreState);
        auto json = _jsonService->assembleJsonAddScoreValues(tournament(),_indexController->roundIndex(),
                                                             _indexController->setIndex(),_scoreController->winnerId(),
                                                             currentActivePlayerId(),score);
        emit requestAddDartsScore(json);
    }

    void DartsScoreMultiAttempt::handleRequestFromUI()
    {
        if(status() == ControllerState::Initialized)
        {
            emit controllerIsInitializedAndReady();
        }
        else if(status() == ControllerState::AddScoreState)
        {
            nextTurn();
        }
        else if(status() == ControllerState::UndoState)
        {
            setCurrentStatus(ControllerState::AwaitsInput);
            sendCurrentTurnValues();
        }
        else if(status() == ControllerState::RedoState)
        {
            setCurrentStatus(ControllerState::AwaitsInput);
            sendCurrentTurnValues();
        }
        else if(status() == ControllerState::WinnerDeclared)
        {
            auto json = _jsonService->assembleJsonWinnerName(tournament(),
                                                             _scoreController->winnerId());
            emit winnerDeclared(json);
        }
        else if(status() == ControllerState::resetState)
        {
            setCurrentStatus(ControllerState::Initialized);
            emit controllerIsInitializedAndReady();
        }
    }

    void DartsScoreMultiAttempt::nextTurn()
    {
        _indexController->next();
        setCurrentStatus(ControllerState::AwaitsInput);
        sendCurrentTurnValues();
    }

    void DartsScoreMultiAttempt::declareWinner()
    {
        auto index = _indexController->setIndex();
        auto currentPlayerId = _scoreController->playerIdAtIndex(index);
        _scoreController->setWinner(currentPlayerId);
        setCurrentStatus(ControllerState::WinnerDeclared);
    }

    DartsScoreMultiAttempt *DartsScoreMultiAttempt::setAssembleDartsScoreTurnValues(DartsScoreTurnValuesBuilderService *newAssembleDartsScoreTurnValues)
    {
        _assembleDartsScoreTurnValues = newAssembleDartsScoreTurnValues;
        return this;
    }

    DartsScoreMultiAttempt *DartsScoreMultiAttempt::setAssembleDartsScoreIndexesByJson(IUnaryService<const QByteArray &, const IDartsMultiAttemptIndexes *> *newAssembleDartsScoreIndexesByJson)
    {
        _assembleDartsScoreIndexesByJson = newAssembleDartsScoreIndexesByJson;
        return this;
    }

    DartsScoreMultiAttempt *DartsScoreMultiAttempt::setAddAccumulatedScoreToModel(IBinaryService<const DartsScore *, const int &, const DartsScore *> *newAddAccumulatedScoreToModel)
    {
        _addAccumulatedScoreToModel = newAddAccumulatedScoreToModel;
        return this;
    }

    DartsScoreMultiAttempt *DartsScoreMultiAttempt::setDetermineControllerStateByWinnerId(IUnaryService<const QUuid &, int> *newDetermineControllerStateByWinnerId)
    {
        _determineControllerStateByWinnerId = newDetermineControllerStateByWinnerId;
        return this;
    }

    DartsScoreMultiAttempt *DartsScoreMultiAttempt::setAssembleDartsPlayerByJson(IUnaryService<const QByteArray &, const IDartsPlayer *> *newAssembleDartsPlayerByJson)
    {
        _assembleDartsPlayerByJson = newAssembleDartsPlayerByJson;
        return this;
    }

    DartsScoreMultiAttempt *DartsScoreMultiAttempt::setAssembleDartsScoresByJsonService(IUnaryService<const QByteArray &, DartsScores> *newAssembleDartsScoresByJsonService)
    {
        _assembleDartsScoresByJsonService = newAssembleDartsScoresByJsonService;
        return this;
    }

    DartsScoreMultiAttempt *DartsScoreMultiAttempt::setAssembleDartsScoreByJsonService(IUnaryService<const QByteArray &, const DartsScore *> *newAssembleDartsScoreByJsonService)
    {
        _assembleDartsScoreByJsonService = newAssembleDartsScoreByJsonService;
        return this;
    }

    DartsScoreMultiAttempt *DartsScoreMultiAttempt::setJsonService(MultiAttemptJsonService *jsonService)
    {
        _jsonService = jsonService;
        return this;
    }

    int DartsScoreMultiAttempt::currentStatus() const
    {
        return _currentStatus;
    }

    void DartsScoreMultiAttempt::initializeControllerIndexes(const QByteArray& json)
    {
        auto indexes = _assembleDartsScoreIndexesByJson->service(json);
        _indexController->setIndexes(indexes->totalTurns(),indexes->turns(),
                                      indexes->roundIndex(),indexes->setIndex());
        emit requestTournamentAssignedPlayerDetails(tournament());
    }

    bool DartsScoreMultiAttempt::isBusy()
    {
        if(status() == Stopped ||
                status() == WinnerDeclared)
        {
            emit controllerIsStopped();
            return true;
        }
        if(status() == ControllerState::AddScoreState)
        {
            return true;
        }
        return false;
    }

    void DartsScoreMultiAttempt::processDomain(const int &domain,
                                             const int &score)
    {
        switch (domain)
        {
            case InputOutOfRange : sendCurrentTurnValues();break;
            case PointDomain : addPoint(score);break;
            case CriticalDomain : addPoint(score);break;
            case TargetDomain : {
                declareWinner();
                addPoint(score);
                break;
            }
            case OutsideDomain : addPoint(0);break;
        }
    }

    DartsScoreMultiAttempt* DartsScoreMultiAttempt::setScoreController(PlayerScoreService *scoreController)
    {
        _scoreController = scoreController;
        return this;
    }

    DartsScoreMultiAttempt* DartsScoreMultiAttempt::setIndexController(IDartsMultiAttemptIndexService *indexController)
    {
        _indexController = indexController;
        return this;
    }

    DartsScoreMultiAttempt *DartsScoreMultiAttempt::setInputValidator(IScoreValidator *scoreEvaluator)
    {
        _scoreEvaluator = scoreEvaluator;
        return this;
    }

    void DartsScoreMultiAttempt::setCurrentStatus(int currentStatus)
    {
        _currentStatus = currentStatus;
    }

    DartsScoreMultiAttempt *DartsScoreMultiAttempt::createInstance(const QUuid &tournament)
    {
        return new DartsScoreMultiAttempt(tournament);
    }

    IDartsLogisticsService<QString> *DartsScoreMultiAttempt::pointLogisticInterface() const
    {
        return _scoreLogisticInterface;
    }

    DartsScoreMultiAttempt *DartsScoreMultiAttempt::setLogisticInterface(IDartsLogisticsService<QString> *pointLogisticInterface)
    {
        _scoreLogisticInterface = pointLogisticInterface;
        return this;
    }

    void DartsScoreMultiAttempt::beginInitialize()
    {
        auto tournamentId = tournament();
        emit requestDartsTournamentIndexes(tournamentId);
    }

    void DartsScoreMultiAttempt::undoSuccess(const QByteArray& json)
    {
        auto dartsScoreModel = DartsScore::fromJson(json);
        auto newScore = _scoreController->addPlayerScore(dartsScoreModel->playerId(),dartsScoreModel->score());
        _addAccumulatedScoreToModel->service(dartsScoreModel,newScore);
        emit scoreRemoved(dartsScoreModel->toJson());
    }

    void DartsScoreMultiAttempt::redoSuccess(const QByteArray& json)
    {
        auto dartsScoreModel = DartsScore::fromJson(json);
        auto newScore = _scoreController->subtractPlayerScoreByModel(dartsScoreModel);
        _addAccumulatedScoreToModel->service(dartsScoreModel,newScore);
        emit scoreAddedSuccess(dartsScoreModel->toJson());
    }

    void DartsScoreMultiAttempt::initializeControllerPlayerDetails(const QByteArray &json)
    {
        auto dartsPlayerModesl = _assembleDartsPlayersByJson->service(json);
        _indexController->setPlayersCount(dartsPlayerModesl.count());
        for (const auto &dartsPlayerModel : dartsPlayerModesl)
            _scoreController->addPlayerEntity(dartsPlayerModel->playerId(),dartsPlayerModel->playerName());
        emit requestTournamentDartsScores(tournament());
    }

    void DartsScoreMultiAttempt::initializeControllerDartsScores(const QByteArray &json)
    {

        auto dartsScores= _assembleDartsScoresByJsonService->service(json);
        _scoreController->subtractPlayerScoreByModels(dartsScores);
        emit requestTournamentWinnerIdAndName(tournament());
    }

    void DartsScoreMultiAttempt::initializeControllerWinnerIdAndName(const QByteArray &json)
    {
        auto dartsPlayer = _assembleDartsPlayerByJson->service(json);
        _scoreController->setWinner(dartsPlayer->playerId());
        auto status = _determineControllerStateByWinnerId->service(dartsPlayer->playerId());
        setCurrentStatus(status);
        emit controllerIsInitialized();
    }
    DartsScoreMultiAttempt *DartsScoreMultiAttempt::setAssembleDartsPlayersByJson(IUnaryService<const QByteArray &, IDartsPlayers> *newAssembleDartsPlayersByJson)
    {
        _assembleDartsPlayersByJson = newAssembleDartsPlayersByJson;
        return this;
    }
}
