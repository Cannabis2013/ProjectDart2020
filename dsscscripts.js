function initializeComponent()
{
    connectInterface();
    applicationInterface.requestCurrentTournamentId();
}

function connectInterface()
{
    applicationInterface.sendDartsTournamentData.connect(handleTournamentMetaData);
    applicationInterface.sendDartsScores.connect(recieveDartsScores);
    applicationInterface.dartsControllerIsReady.connect(backendIsReady);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
    applicationInterface.controllerHasDeclaredAWinner.connect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.addedInput.connect(backendPersistedInput);
    scoreKeyPad.sendInput.connect(handleScoreKeyPadInput);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
    applicationInterface.dartsInputRemoveSucces.connect(backendRemovedPoint);
}

function disconnectInterface()
{
    applicationInterface.sendDartsTournamentData.disconnect(handleTournamentMetaData);
    applicationInterface.sendDartsScores.disconnect(recieveDartsScores);
    applicationInterface.dartsControllerIsReady.disconnect(backendIsReady);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
    applicationInterface.controllerHasDeclaredAWinner.disconnect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.disconnect(backendIsStopped);
    applicationInterface.addedInput.disconnect(backendPersistedInput);
    applicationInterface.dartsInputRemoveSucces.disconnect(backendRemovedPoint);
    scoreKeyPad.sendInput.disconnect(handleScoreKeyPadInput);
}

function handleTournamentMetaData(data){
    var json = JSON.parse(data);
    dartsMetaValues.title = json["title"];
    dartsMetaValues.winnerName= json["winnerName"];
    dartsMetaValues.keyPoint = json["keyPoint"];
    dartsMetaValues.attempts = json["attempts"];
    dartsMetaValues.assignedPlayerNames = json["assignedPlayerNames"];
    initializeScoreBoard();
    applicationInterface.requestDartsScores();
}

function initializeScoreBoard()
{
    var assignedPlayerNames = dartsMetaValues.assignedPlayerNames;
    var keyPoint = dartsMetaValues.keyPoint;
    singleColumnScoreBoard.appendHeaderData(assignedPlayerNames,keyPoint);
}

function controllerIsReady()
{
    dartsScoreSingleColumnBody.state = "ready";
}

function recieveDartsScores(scores)
{
    var json = JSON.parse(scores);
    addDartsScoresToScoreBoard(json);
    applicationInterface.requestControllerState();
}

function addDartsScoresToScoreBoard(json)
{
    for(var i = 0;i < json.length;++i)
        addToScoreBoard(json[i]);
}

function addToScoreBoard(json)
{
    var playerName = json["playerName"];
    var playerScore = json["totalScore"];
    singleColumnScoreBoard.setData(playerName,playerScore);
}

// When backend has evaluated and persisted player input
function backendPersistedInput(data)
{
    var json = JSON.parse(data);
    addToScoreBoard(json);
    setSuggestedTargetRow(json);
    setTurnControllerValues(json);
    dartsScoreSingleColumnBody.state = "waitingForInput";
}

function reinitialize()
{
    singleColumnScoreBoard.clearData();
    singleColumnScoreTurnController.reset();
    keyDataDisplay.clear();
    initializeScoreBoard();
    dartsScoreSingleColumnBody.state = "ready";
}

function resetTournament()
{
    dartsScoreSingleColumnBody.state = "stopped";
    applicationInterface.requestTournamentReset();
}

function backendRemovedPoint(data)
{
    var json = JSON.parse(data);
    setTurnControllerValues(json);
    addToScoreBoard(json);
    dartsScoreSingleColumnBody.state = "waitingForInput";
}

function setSuggestedTargetRow(json)
{
    let throwSuggestion = json["targetRow"];
    keyDataDisplay.setThrowSuggestion(throwSuggestion);
}

function setTurnControllerValues(json)
{
    singleColumnScoreTurnController.leftButtonEnabled = json["canUndo"];
    singleColumnScoreTurnController.rightButtonEnabled = json["canRedo"];
    singleColumnScoreTurnController.currentRoundIndex = json["roundIndex"];
    singleColumnScoreTurnController.currentPlayer = json["currentPlayerName"];
}

function handleScoreKeyPadInput(value){
    dartsScoreSingleColumnBody.state = "waitingForInputConfirmation";
    var obj = {
        score : value
    };
    var json = JSON.stringify(obj);
    applicationInterface.addUserInput(json);
}

function backendIsStopped()
{
    if(dartsScoreSingleColumnBody.state !== "preRestart")
        dartsScoreSingleColumnBody.state = "stopped";
}

function backendDeclaredAWinner(data)
{
    var json = JSON.parse(data);
    dartsMetaValues.winnerName = json["winnerName"];
    dartsScoreSingleColumnBody.state = "winner";
}

function undoClicked()
{
    dartsScoreSingleColumnBody.state = "waitingForInputConfirmation";
    applicationInterface.requestUndo();
}

function redoClicked()
{
    dartsScoreSingleColumnBody.state = "waitingForInputConfirmation";
    applicationInterface.requestRedo();
}

function setWinnerText()
{
    keyDataDisplay.setCurrentWinner(dartsMetaValues.winnerName);
}

function backendIsReadyAndAwaitsInput(data)
{
    var json = JSON.parse(data);
    setSuggestedTargetRow(json);
    setTurnControllerValues(json);
    dartsScoreSingleColumnBody.state = "waitingForInput";
}

function backendIsReady()
{
    dartsScoreSingleColumnBody.state = "ready";
}
