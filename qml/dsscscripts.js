function initializeComponent()
{
    connectInterface();
    getMetaData();
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
    scoreKeyPad.sendInput.connect(handleScoreKeyPadInput);
}

function disconnectInterface()
{
    applicationInterface.sendDartsTournamentData.disconnect(handleMetaData);
    applicationInterface.sendDartsScores.disconnect(recieveScores);
    applicationInterface.controllerReady.disconnect(controllerReady);
    applicationInterface.controllerStopped.disconnect(backendIsStopped);
    applicationInterface.winnerFound.disconnect(winnerFound);
    applicationInterface.sendDartsScore.disconnect(updatePlayerScore);
    applicationInterface.updateDartsTurnValues.connect(updateTurnValues);
    scoreKeyPad.sendInput.disconnect(handleScoreKeyPadInput);
}

function getMetaData(){
    var id = dsController.tournamentId();
    var byteArray = dartsContext.tournament(id);
    var json = JSON.parse(byteArray);
    dartsMetaValues.title = json["title"];
    dartsMetaValues.winnerName= json["winnerName"];
    dartsMetaValues.keyPoint = json["keyPoint"];
    dartsMetaValues.assignedPlayerNames = getPlayerNames(json["assignedPlayerDetails"]);
    initializeScoreBoard();
    preferedPageTitle = dartsMetaValues.title;
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

function recieveScores(scores)
{
    var json = JSON.parse(scores);
    addDartsScoresToScoreBoard(json);
    applicationInterface.requestControllerState();
}

function controllerReady()
{
    dsscContent.state = "ready";
}

function addDartsScoresToScoreBoard(json)
{
    for(var i = 0;i < json.length;++i)
        addToScoreBoard(json[i]);
}

function addToScoreBoard(json)
{
    let playerName = json["inputPlayerName"];
    let playerScore = json["remainingScore"];
    let middleValue = json["middleValue"];
    let minimum = json["minimumValue"];
    let maximum = json["maximumValue"];
    singleColumnScoreBoard.setData(playerName,playerScore,minimum,middleValue,maximum);
}

function updatePlayerScore(data)
{
    var json = JSON.parse(data);
    addToScoreBoard(json);
    applicationInterface.dartsNextTurn();
}

function updateTurnValues(data)
{
    var json = JSON.parse(data);
    setTurnControllerValues(json);
    setSuggestedTargetRow(json);
    dsscContent.state = "waitingForInput";
}

function reinitialize()
{
    singleColumnScoreBoard.clearData();
    singleColumnScoreTurnController.reset();
    keyDataDisplay.clear();
    initializeScoreBoard();
    dsscContent.state = "ready";
}

function resetTournament()
{
    dsscContent.state = "stopped";
    applicationInterface.requestTournamentReset();
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
    singleColumnScoreTurnController.currentRoundIndex = json["currentRoundIndex"];
    singleColumnScoreTurnController.currentPlayer = json["currentPlayerName"];
}

function handleScoreKeyPadInput(value){
    dsscContent.state = "waitingForInputConfirmation";
    var obj = {
        score : value
    };
    var json = JSON.stringify(obj);
    applicationInterface.addUserInput(json);
}

function backendIsStopped()
{
    if(dsscContent.state !== "preRestart")
        dsscContent.state = "stopped";
}

function winnerFound(data)
{
    var json = JSON.parse(data);
    dartsMetaValues.winnerName = json["winnerName"];
    keyDataDisplay.setThrowSuggestion("");
    dsscContent.state = "winner";
}

function undoClicked()
{
    dsscContent.state = "waitingForInputConfirmation";
    applicationInterface.dartsUndo();
}

function redoClicked()
{
    dsscContent.state = "waitingForInputConfirmation";
    applicationInterface.dartsRedo();
}

function setWinnerText()
{
    keyDataDisplay.setCurrentWinner(dartsMetaValues.winnerName);
}
