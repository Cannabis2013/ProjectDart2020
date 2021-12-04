function init()
{
    initMetaData();
    initializeScoreBoard();
    updateScoreBoard();
    preferedPageTitle = metaValues.title;
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
function initMetaData()
{
    let json = getMetaData();
    metaValues.title = json["title"];
    metaValues.winnerName= json["winnerName"];
    metaValues.initRemScore = json["initRemScore"];
    metaValues.assignedPlayerNames = getPlayerNames(json["assignedPlayerDetails"]);
}
function getMetaData(){
    var id = dsController.tournamentId();
    var json = dartsContext.tournament(id);
    return JSON.parse(json);
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
    var initRemScore = metaValues.initRemScore;
    singleColumnScoreBoard.appendHeaderData(assignedPlayerNames,initRemScore);
}

function updateScoreBoard()
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
}
function resetTournament()
{
    dsscContent.state = "stopped";
    var result = dsController.reset();
    if(result)
    {
        reinitialize();
        dsscContent.state = "ready";
    }
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
    var response = addScore(value);
    addToScoreBoard(response);
    updateTurnValues();
    setState("waitingForInput");
}
function addScore(score)
{
    var obj = {score : score};
    var json = JSON.stringify(obj);
    var response = dsController.addInput(json);
    return JSON.parse(response);
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
    var response = dsController.undoTurn();
    addToScoreBoard(JSON.parse(response));
    updateTurnValues();
    setState("waitingForInput");
}

function redoClicked()
{
    dsscContent.state = "waitingForInputConfirmation";
    var response = dsController.redoTurn();
    addToScoreBoard(JSON.parse(response));
    updateTurnValues();
    setState("waitingForInput");
}
