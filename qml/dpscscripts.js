function init()
{
    connectInterface();
    let metaJson = getMetaData();
    initMetaData(metaJson);
    updateScoresView();
    setState("ready");
}

function connectInterface()
{
    dpController.updatePlayerScore.connect(processScore);
    dpController.resetSucces.connect(reinitialize);
}

function disconnectInterface()
{
    dpController.updatePlayerScore.disconnect(processScore);
    dpController.resetSucces.disconnect(reinitialize);
}
function getMetaData(){
    var id = dpController.tournamentId();
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

function updateScoresView()
{
    let scores = dpController.getPlayerScores();
    var json = JSON.parse(scores);
    addDartsScoresToScoreBoard(json);
}

function setState(state)
{
    var status = dpController.status();
    if(status === 0)
        dpscContent.state = state;
    else if(status === 2)
        setWinnerState();
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

function processScore(json)
{
    addToScoreBoard(JSON.parse(json));
    updateTurnValues();
    setState("waitingForInput");
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

function resetTournament()
{
    dpscContent.state = "stopped";
    dpController.reset();
}
function reinitialize()
{
    dpscScoreBoard.clearData();
    pointSingleColumnTurnController.reset();
    keyDataDisplay.clear();
    initializeScoreBoard();
    dpscContent.state = "ready";
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
    if(dpController.handleInput(json) === -1)
        inputNotAdded();
}
function inputNotAdded()
{
    dsscContent.state = "ready";
}
function backendIsStopped()
{
    if(dpscContent.state !== "preRestart")
        dpscContent.state = "stopped";
}

function setWinnerState(data)
{
    var json = JSON.parse(data);
    metaValues.winnerName = json["winnerName"];
    dpscContent.state = "winner";
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
        dpscContent.state = "waitingForInput";
    }
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
}

function pauseClicked()
{
    dpscContent.state = "stopped";
}

function setWinnerText()
{
    keyDataDisplay.setCurrentWinner(metaValues.winnerName);
}
