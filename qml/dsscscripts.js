function initializeComponent()
{
    connectInterface();
    applicationInterface.requestCurrentTournamentId();
}

function connectInterface()
{
    applicationInterface.sendDartsTournamentData.connect(handleMetaData);
    applicationInterface.sendDartsScores.connect(recieveScores);
    applicationInterface.dartsControllerIsReady.connect(backendIsReady);
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
    applicationInterface.controllerHasDeclaredAWinner.connect(backendDeclaredAWinner);
    applicationInterface.addedInput.connect(backendAddedInput);
    applicationInterface.dartsInputRemoveSucces.connect(backendRemovedPoint);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
    scoreKeyPad.sendInput.connect(handleScoreKeyPadInput);
}

function disconnectInterface()
{
    applicationInterface.sendDartsTournamentData.disconnect(handleMetaData);
    applicationInterface.sendDartsScores.disconnect(recieveScores);
    applicationInterface.dartsControllerIsReady.disconnect(backendIsReady);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
    applicationInterface.controllerHasDeclaredAWinner.disconnect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.disconnect(backendIsStopped);
    applicationInterface.addedInput.disconnect(backendAddedInput);
    applicationInterface.dartsInputRemoveSucces.disconnect(backendRemovedPoint);
    scoreKeyPad.sendInput.disconnect(handleScoreKeyPadInput);
}

function handleMetaData(data){
    var json = JSON.parse(data);
    dartsMetaValues.title = json["title"];
    dartsMetaValues.winnerName= json["winnerName"];
    dartsMetaValues.keyPoint = json["keyPoint"];
    dartsMetaValues.assignedPlayerNames = getPlayerNames(json["assignedPlayerDetails"]);
    initializeScoreBoard();
    applicationInterface.requestDartsScores();
}

function getPlayerNames(playerDetails)
{
    let playerNames = [];
    let count = playerDetails.length;
    for(var i = 0;i < count;i++)
    {
        let playerDetail = playerDetails[i];
        let playerName = playerDetail["playerName"];
        playerNames.push(playerName);
    }
    return playerNames;
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

function recieveScores(scores)
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
    var playerName = json["inputPlayerName"];
    var playerScore = json["totalScore"];
    singleColumnScoreBoard.setData(playerName,playerScore);
}

function backendAddedInput(data)
{
    var json = JSON.parse(data);
    addToScoreBoard(json);
    setSuggestedTargetRow(json);
    setTurnControllerValues(json);
    applicationInterface.requestControllerState();
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
    let throwSuggestion = json["suggestedFinish"];
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
