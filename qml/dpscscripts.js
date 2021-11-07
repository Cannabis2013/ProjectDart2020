function initializeComponent()
{
    connectInterface();
    applicationInterface.requestCurrentTournamentId();
}

function connectInterface()
{
    applicationInterface.sendDartsTournamentData.connect(handleMetaData);
    applicationInterface.sendDartsScores.connect(recieveScores);
    applicationInterface.controllerReady.connect(controllerReady);
    applicationInterface.controllerStopped.connect(backendIsStopped);
    applicationInterface.winnerFound.connect(winnerFound);
    applicationInterface.sendDartsScore.connect(updatePlayerScore);
    applicationInterface.updateDartsTurnValues.connect(updateTurnValues);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
}

function disconnectInterface()
{
    applicationInterface.sendDartsTournamentData.disconnect(handleMetaData);
    applicationInterface.sendDartsScores.disconnect(recieveScores);
    applicationInterface.controllerReady.disconnect(controllerReady);
    applicationInterface.controllerStopped.connect(backendIsStopped);
    applicationInterface.updateDartsTurnValues.disconnect(updateTurnValues);
    applicationInterface.winnerFound.disconnect(winnerFound);
    applicationInterface.sendDartsScore.disconnect(updatePlayerScore);
    applicationInterface.dartsControllerIsReset.disconnect(reinitialize);
}

function handleMetaData(data){
    var json = JSON.parse(data);
    metaValues.title = json["title"];
    metaValues.winnerName= json["winnerName"];
    metaValues.keyPoint = json["keyPoint"];
    metaValues.assignedPlayerNames = getPlayerNames(json["assignedPlayerDetails"]);
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
    var assignedPlayerNames = metaValues.assignedPlayerNames;
    var keyPoint = metaValues.keyPoint;
    dpscScoreBoard.appendHeaderData(assignedPlayerNames,keyPoint);
}

function recieveScores(scores)
{
    var json = JSON.parse(scores);
    addDartsScoresToScoreBoard(json);
    applicationInterface.requestControllerState();
}

function controllerReady()
{
    dpscContent.state = "ready";
}

function addDartsScoresToScoreBoard(json)
{
    for(var i = 0;i < json.length;++i)
        addToScoreBoard(json[i]);
}

function updatePlayerScore(data)
{
    var json = JSON.parse(data);
    addToScoreBoard(json);
    applicationInterface.dartsNextTurn();
}

function updateTurnValues(data)
{
    setThrowSuggestion(json);
    setTurnControllerValues(json);
    applicationInterface.requestControllerState();
}

function addToScoreBoard(json)
{
    let playerName = json["inputPlayerName"];
    let playerPoint = json["point"];
    let playerScore = json["remainingScore"];
    let minimum = json["minimumValue"];
    let middleValue = json["middleValue"];
    let maximum = json["maximumValue"];
    let inGame = json["inGame"];
    dpscScoreBoard.setData(playerName,playerScore,minimum,middleValue,maximum,inGame);
}

function setThrowSuggestion(json)
{
    keyDataDisplay.setThrowSuggestion(json["suggestedFinish"]);
}

function resetTournament()
{
    dpscContent.state = "stopped";
    applicationInterface.requestTournamentReset();
}

function reinitialize()
{
    dpscScoreBoard.clearData();
    pointSingleColumnTurnController.reset();
    keyDataDisplay.clear();
    initializeScoreBoard();
    dpscContent.state = "ready";
}

function handleRequestTournamentReset()
{
    dpscContent.state = "stopped";
    applicationInterface.requestTournamentReset();
}

function setTurnControllerValues(json)
{
    pointSingleColumnTurnController.leftButtonEnabled = json["canUndo"];
    pointSingleColumnTurnController.rightButtonEnabled = json["canRedo"];
    pointSingleColumnTurnController.currentRoundIndex = json["currentRoundIndex"];
    pointSingleColumnTurnController.currentPlayer = json["currentPlayerName"];
}

function handleScoreKeyPadInput(input, keyCode){
    dpscContent.state = "waitingForInputConfirmation";
    var obj = {
        point : input,
        modKeyCode : keyCode
    };
    var json = JSON.stringify(obj);
    applicationInterface.addUserInput(json);
}

function backendIsStopped()
{
    if(dpscContent.state !== "preRestart")
        dpscContent.state = "stopped";
}

function winnerFound(data)
{
    var json = JSON.parse(data);
    metaValues.winnerName = json["winnerName"];
    dpscContent.state = "winner";
}

function updateTurnValues(data)
{
    var json = JSON.parse(data);
    setThrowSuggestion(json);
    setTurnControllerValues(json);
    dpscContent.state = "waitingForInput";
}

function undoClicked()
{
    dpscContent.state = "waitingForInputConfirmation";
    dartsUndo();
    applicationInterface.dartsUndo();
}

function redoClicked()
{
    dpscContent.state = "waitingForInputConfirmation";
    applicationInterface.dartsRedo();
}

function pauseClicked()
{
    dpscContent.state = "stopped";
    applicationInterface.requestStopGame();
}

function setWinnerText()
{
    keyDataDisplay.setCurrentWinner(metaValues.winnerName);
}
