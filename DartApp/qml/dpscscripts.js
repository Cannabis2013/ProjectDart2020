function init()
{
    var metaVals = initMetaData();
    initSBHeader(metaVals);
    initSBFields();
    setState("ready");
}
function getMetaData(){
    var id = dpController.tournamentId();
    var byteArray = dartsContext.tournament(id);
    return JSON.parse(byteArray);
}
function initMetaData()
{
    let json = getMetaData();
    var metaVals = {
        title : json["title"],
        winnerName : json["winnerName"],
        initRemScore : json["initRemScore"],
        assignedPlayerNames : getPlayerNames(json["players"])
    };
    return metaVals;
}
function initSBFields()
{
    let scores = dpController.getPlayerScores();
    var json = JSON.parse(scores);
    addDartsScoresToScoreBoard(json);
}
function setState(state)
{
    var status = dpController.status();
    if(status === 0)
        dpcContent.state = state;
    else if(status === 2)
        winnerFound();
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
function initSBHeader(metaVals)
{
    var playerNames = metaVals.assignedPlayerNames;
    var initRemScore = metaVals.initRemScore;
    dpscScoreBoard.appendHeaderData(playerNames,initRemScore);
}
function controllerReady()
{
    dpcContent.state = "ready";
}
function addDartsScoresToScoreBoard(json)
{
    for(var i = 0;i < json.length;++i)
        updateScoreBoard(json[i]);
}

function updateScoreBoard(json)
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
function resetTournament()
{
    dpcContent.state = "stopped";
    var result = dpController.reset();
    if(result)
    {
        clearComponents();
        init();
    }
}
function clearComponents()
{
    dpscScoreBoard.clearData();
    pointSingleColumnTurnController.reset();
    keyDataDisplay.clear();
}
function setTurnControllerValues(json)
{
    pointSingleColumnTurnController.leftButtonEnabled = json["canUndo"];
    pointSingleColumnTurnController.rightButtonEnabled = json["canRedo"];
    pointSingleColumnTurnController.currentRoundIndex = json["currentRoundIndex"];
    pointSingleColumnTurnController.currentPlayer = json["currentPlayerName"];
}
function handleScoreKeyPadInput(input, keyCode){
    dpcContent.state = "waitingForInputConfirmation";
    var response = addInput(input,keyCode);
    updateScoreBoard(response);
    updateTurnValues();
    setState("waitingForInput");
}
function addInput(input,modCode)
{
    var json = createInputJson(input,modCode);
    let response = dpController.addInput(JSON.stringify(obj));
    return JSON.parse(response);
}

function createInputJson(input,modCode)
{
    var obj = {
        point : input,
        modKeyCode : modCode
    };
    return JSON.stringify(obj);
}

function backendIsStopped()
{
    if(dpcContent.state !== "preRestart")
        dpcContent.state = "stopped";
}
function winnerFound()
{
    var byteArray = dpController.getWinnerJson();
    var json = JSON.parse(byteArray);
    keyDataDisplay.setCurrentWinner(json["winnerName"]);
    keyDataDisplay.setThrowSuggestion("");
    dpcContent.state = "winner";
}
function updateTurnValues()
{
    var byteArray = dpController.getTurnValues();
    var json = JSON.parse(byteArray);
    setTurnControllerValues(json);
    keyDataDisplay.setThrowSuggestion(json["finishCandidate"]);
}
function startGame()
{
    let status = dpController.status();
    if(status === 0)
    {
        updateTurnValues();
        dpcContent.state = "waitingForInput";
    }
}
function undoClicked()
{
    dpcContent.state = "waitingForInputConfirmation";
    var response = dpController.undoTurn();
    updateScoreBoard(JSON.parse(response));
    updateTurnValues();
    setState("waitingForInput");
}

function redoClicked()
{
    dpcContent.state = "waitingForInputConfirmation";
    var response = dpController.redoTurn();
    updateScoreBoard(JSON.parse(response));
    updateTurnValues();
    setState("waitingForInput");
}

function pauseClicked()
{
    dpcContent.state = "stopped";
}
