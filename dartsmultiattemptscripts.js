function initializeComponent()
{
    connectInterface();
    requestControllerValues();
}

function handleFTPTournamentMetaData(data){
    var json = JSON.parse(data);
    dartsSingleAttemptValues.title = json["title"];
    dartsSingleAttemptValues.winnerName= json["winnerName"];
    dartsSingleAttemptValues.keyPoint = json["keyPoint"];
    dartsSingleAttemptValues.attempts = json["attempts"];
    dartsSingleAttemptValues.assignedPlayerNames = json["assignedPlayerNames"];
    initializeScoreBoard();
    requestSingleAttemptPoints();
}

function initializeScoreBoard()
{
    var assignedPlayerNames = dartsSingleAttemptValues.assignedPlayerNames;
    var keyPoint = dartsSingleAttemptValues.keyPoint;
    multiPointScoreBoard.appendHeaderData(assignedPlayerNames,keyPoint);
}

function controllerIsInitializedAndReady()
{
    dartsMultiAttemptBody.state = "ready";
}

function recieveDartsSingleAttemptPoints(scores)
{
    var jsonData = JSON.parse(scores);
    var count = jsonData.length;
    for(var i = 0;i < count;++i)
    {
        var entity = jsonData[i];
        var playerName = entity["playerName"];
        var playerScore = entity["score"];
        multiAttemptScoreBoard.setData(playerName,playerScore);
    }
    dartsMultiAttemptBody.requestStatusFromBackend();
}

// When backend has evaluated and persisted player input
function extractPointScoreFromJson(data)
{
    var json = JSON.parse(data);
    let playerName = json["playerName"];
    let scoreValue = json["score"];
    multiPointScoreBoard.setData(playerName,pointValue,scoreValue);
    requestStatusFromBackend();
}

function reinitialize()
{
    // reinitialize controller after reset
    multiPointScoreBoard.clearData();
    initializeScoreBoard();
    requestStatusFromBackend();
}

function handleRequestTournamentReset()
{
    if(dartsMultiAttemptBody.state === "ready")
        dartsMultiAttemptBody.state = "stopped";
}

function backendRemovedPoint(data)
{
    var json = JSON.parse(data);
    let playerName = json["playerName"];
    multiAttemptScoreBoard.setData(player,point,score,-1);
    requestStatusFromBackend();
}

function backendIsReadyAndAwaitsInput(data)
{
    var json = JSON.parse(data);
    let canUndo = json.canUndo;
    let canRedo = json.canRedo;
    let currentRoundIndex = json.roundIndex;
    let currentPlayerUserName = json.currentUserName;
    let throwSuggestion = json.targetRow;
    let suggestion = textSourceContainer.throwSuggestLabel + " " + throwSuggestion;
    notificationItemSlot.setThrowSuggestion(suggestion);
    multiPointTurnController.updateState(currentRoundIndex,
                                         currentPlayerUserName,
                                         canUndo,
                                         canRedo);
    dartsMultiAttemptBody.state = "waitingForInput";
}

function handlePointKeyPadInput(value,keyCode){
    dartsMultiAttemptBody.state = "waitingForInputConfirmation";
    var obj = {
        point : value,
        modKeyCode : keyCode
    };
    var json = JSON.stringify(obj);
    dartsMultiAttemptBody.sendInput(json);
}

function backendIsStopped()
{
    if(dartsMultiAttemptBody.state !== "preRestart")
        dartsMultiAttemptBody.state = "stopped";
}

function backendIsInitialized()
{
    dartsMultiAttemptBody.state = "ready";
}

function backendDeclaredAWinner(data)
{
    var json = JSON.parse(data);
    tournamentMetaData.determinedWinner = json.winner;
    dartsMultiAttemptBody.state = "winner";
}

function undoClicked()
{
    dartsMultiAttemptBody.state = "waitingForInputConfirmation";
    requestUndo();
}

function redoClicked()
{
    dartsMultiAttemptBody.state = "waitingForInputConfirmation";
    requestRedo();
}
