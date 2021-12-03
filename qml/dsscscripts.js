function init()
{
    let metaJson = getMetaData();
    initMetaData(metaJson);
    updateScoresView();
    setState("ready");
}
function setState(state)
{
    var status = dsController.status();
    if(status === 0)
        dsscContent.state = state;
    else if(status === 2)
        winnerFound();
}
function connectInterface()
{
    dsController.updatePlayerScore.connect(processScore);
    dsController.resetSucces.connect(reinitialize);
}

function disconnectInterface()
{
    dsController.updatePlayerScore.disconnect(processScore);
    dsController.resetSucces.disconnect(reinitialize);
}
function getMetaData(){
    var id = dsController.tournamentId();
    var byteArray = dartsContext.tournament(id);
    return JSON.parse(byteArray);
}
function initMetaData(json)
{
    metaValues.title = json["title"];
    metaValues.winnerName= json["winnerName"];
    metaValues.keyPoint = json["keyPoint"];
    metaValues.assignedPlayerNames = getPlayerNames(json["assignedPlayerDetails"]);
    initializeScoreBoard();
    preferedPageTitle = metaValues.title;
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
    singleColumnScoreBoard.appendHeaderData(assignedPlayerNames,keyPoint);
}

function updateScoresView()
{
    let scores = dsController.getPlayerScores();
    var json = JSON.parse(scores);
    addDartsScoresToScoreBoard(json);
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
function processScore(data)
{
    addToScoreBoard(JSON.parse(data));
    updateTurnValues();
    setState("waitingForInput");
}
function startGame()
{
    let status = dsController.status();
    if(status === 0)
    {
        updateTurnValues();
        dsscContent.state = "waitingForInput";
    }
}
function updateTurnValues()
{
    var byteArray = dsController.getTurnValues();
    var json = JSON.parse(byteArray);
    setTurnControllerValues(json);
    keyDataDisplay.setThrowSuggestion(json["finishCandidate"]);
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
    dsController.reset();
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
    var obj = {score : value};
    var json = JSON.stringify(obj);
    if(dsController.handleInput(json) === -1)
        inputNotAdded();
}
function inputNotAdded()
{
    dsscContent.state = "ready";
}
function backendIsStopped()
{
    if(dsscContent.state !== "preRestart")
        dsscContent.state = "stopped";
}
function winnerFound()
{
    var byteArray = dsController.getWinnerJson();
    var json = JSON.parse(byteArray);
    keyDataDisplay.setCurrentWinner(json["winnerName"]);
    keyDataDisplay.setThrowSuggestion("");
    dsscContent.state = "winner";
}
function undoClicked()
{
    dsscContent.state = "waitingForInputConfirmation";
    dsController.undoTurn();
}

function redoClicked()
{
    dsscContent.state = "waitingForInputConfirmation";
    dsController.redoTurn();
}
