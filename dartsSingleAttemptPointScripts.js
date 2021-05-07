function initializeComponent()
{
    connectInterface();
    requestControllerValues();
}

function connectInterface()
{
    dartsSingleAttemptBody.requestControllerValues.connect(applicationInterface.handleTournamentMetaRequest);
    dartsSingleAttemptBody.requestSingleAttemptPoints.connect(
                applicationInterface.handleRequestForDartsSingleAttemptPoints);
    applicationInterface.sendAssembledDartsSingleAttemptPoints.connect(
                recieveDartsSingleAttemptPoints);
    applicationInterface.dartsSingleAttemptPointControllerIsReady.connect(controllerIsInitializedAndReady);
    applicationInterface.controllerHasDeclaredAWinner.connect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.dartsSingleAttemptPointControllerIsInitialized.connect(backendIsInitialized);
    applicationInterface.sendDartsTournamentData.connect(handleFTPTournamentMetaData);
    dartsSingleAttemptBody.requestStart.connect(applicationInterface.handleRequestStart);
    dartsSingleAttemptBody.requestStop.connect(applicationInterface.handleRequestStop);
    dartsSingleAttemptBody.requestRestart.connect(applicationInterface.handleRestartTournament);
    dartsSingleAttemptBody.sendInput.connect(applicationInterface.handleSingleAttemptPlayerPointInput);
    dartsSingleAttemptBody.requestStatusFromBackend.connect(applicationInterface.handleControllerStateRequest);
    applicationInterface.dartsControllerRemovedSingleAttemptPoint.connect(backendRemovedPoint);
    dartsSingleAttemptBody.requestUndo.connect(applicationInterface.handleUndoRequest);
    dartsSingleAttemptBody.requestRedo.connect(applicationInterface.handleRedoRequest);

    pointKeyPad.sendInput.connect(handlePointKeyPadInput);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
}

function handleFTPTournamentMetaData(data){
    var json = JSON.parse(data);

    var ftpComponent = Qt.createComponent("FirstToPostMetaData.qml");
    var tournamentTitle = json["title"];
    var determinedWinnerName = json["winnerName"];
    var tournamentGameMode = json["gameMode"];
    var tournamentKeyPoint = json["keyPoint"];
    var attempts = json["attempts"];
    var displayHint = json["displayHint"];
    var inputHint = json["inputHint"];
    var assignedPlayers = json["assignedPlayerNames"];
    requestSingleAttemptPoints();
}

function controllerIsInitializedAndReady()
{
    dartsSingleAttemptBody.state = "ready";
}

function recieveDartsSingleAttemptPoints(scores)
{
    var jsonData = JSON.parse(scores);
    var count = jsonData.length;
    for(var i = 0;i < count;++i)
    {
        var entity = jsonData[i];
        var playerName = entity["playerName"];
        var playerScore = entity["playerAccumulatedScore"];
        var playerPoint = entity["playerPoint"];
        var keyCode = entity["modKeyCode"];
        scoreBoardInterface().setData(playerName,playerScore,playerPoint,keyCode);
    }
    dartsSingleAttemptBody.requestStatusFromBackend();
}

// When backend has evaluated and persisted player input
function extractPointScoreFromJson(data)
{
    var json = JSON.parse(data);
    let playerName = json["playerName"];
    let pointValue = json["point"];
    let keyCode = json["modKeyCode"];
    multiPointScoreBoard.setData(playerName,pointValue,scoreValue,keyCode);
    requestStatusFromBackend();
}

function reinitialize()
{
    // reinitialize controller after reset
}

function handleRequestTournamentReset()
{
    if(dartsSingleAttemptBody.state === "ready")
        dartsSingleAttemptBody.state = "stopped";
}

function backendRemovedPoint(data)
{
    var json = JSON.parse(data);
    let playerName = json["playerName"];
    let scoreValue = json["playerScore"];
    let pointValue = json["playerPoint"];
    alterScore(playerName,scoreValue,pointValue);
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
    dartsSingleAttemptBody.notificationItemSlot.setThrowSuggestion(suggestion);
    dartsSingleAttemptBody.multiPointTurnController.updateState(currentRoundIndex,
                                            currentPlayerUserName,
                                            canUndo,
                                            canRedo);
    gamePageBody.state = "waitingForInput";
}

function handlePointKeyPadInput(value,keyCode){
    gamePageBody.state = "waitingForInputConfirmation";
    var obj = {
        Point : value,
        ModKeyCode : keyCode
    };
    var json = JSON.stringify(obj);
    dartsSingleAttemptBody.sendInput(json);
}

function backendIsStopped()
{
    if(gamePageBody.state !== "preRestart")
        gamePageBody.state = "stopped";
}

function backendIsInitialized()
{
    gamePageBody.state = "ready";
}

function backendDeclaredAWinner(data)
{
    var json = JSON.parse(data);
    tournamentMetaData.determinedWinner = json.winner;
    gamePageBody.state = "winner";
}
