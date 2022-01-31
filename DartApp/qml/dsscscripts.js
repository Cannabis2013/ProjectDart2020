function init()
{
    var metaVals = initMetaData();
    initHeader(metaVals);
    initScoreBoard();
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
    var metaVals = {
        title : json["title"],
        winnerName : json["winnerName"],
        initRemScore : json["initRemScore"],
        assignedPlayerNames : getPlayerNames(json["assignedPlayerDetails"])
    };
    return metaVals;
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
function initHeader(metaVals)
{
    var assignedPlayerNames = metaVals.assignedPlayerNames;
    var initRemScore = metaVals.initRemScore;
    singleColumnScoreBoard.appendHeaderData(assignedPlayerNames,initRemScore);
}

function initScoreBoard()
{
    var scores = dsController.getPlayerScores();
    var json = JSON.parse(scores);
    addDartsScoresToScoreBoard(json);
}

function addDartsScoresToScoreBoard(json)
{
    for(var i = 0;i < json.length;++i)
        updateScoreBoard(json[i]);
}

function updateScoreBoard(json)
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
function resetTournament()
{
    dsscContent.state = "stopped";
    var result = dsController.reset();
    if(result)
    {
        clearComponents();
        init();
    }
}
function clearComponents()
{
    singleColumnScoreBoard.clearData();
    singleColumnScoreTurnController.reset();
    keyDataDisplay.clear();
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
    var response = addInput(value);
    updateScoreBoard(response);
    updateTurnValues();
    setState("waitingForInput");
}
function addInput(score)
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
    updateScoreBoard(JSON.parse(response));
    updateTurnValues();
    setState("waitingForInput");
}

function redoClicked()
{
    dsscContent.state = "waitingForInputConfirmation";
    var response = dsController.redoTurn();
    updateScoreBoard(JSON.parse(response));
    updateTurnValues();
    setState("waitingForInput");
}
