function initializeComponent()
{
    connectInterface();
    requestControllerValues();
}

function connectInterface()
{
    dartsSingleAttemptBody.requestControllerValues.connect(applicationInterface.assembleDartsTournamentValues);
    dartsSingleAttemptBody.requestSingleAttemptPoints.connect(
                applicationInterface.handleRequestForDartsSingleAttemptPoints);
    applicationInterface.sendAssembledDartsSingleAttemptPoints.connect(
                recieveDartsSingleAttemptPoints);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
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
    applicationInterface.dartsControllerAddedAndPersistedScore.connect(extractPointScoreFromJson);
}

function disConnectInterface()
{
    dartsSingleAttemptBody.requestControllerValues.disconnect(applicationInterface.assembleDartsTournamentValues);
    dartsSingleAttemptBody.requestSingleAttemptPoints.disconnect(
                applicationInterface.handleRequestForDartsSingleAttemptPoints);
    applicationInterface.sendAssembledDartsSingleAttemptPoints.disconnect(
                recieveDartsSingleAttemptPoints);
    applicationInterface.dartsSingleAttemptPointControllerIsReady.disconnect(controllerIsInitializedAndReady);
    applicationInterface.controllerHasDeclaredAWinner.disconnect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.disconnect(backendIsStopped);
    applicationInterface.dartsSingleAttemptPointControllerIsInitialized.disconnect(backendIsInitialized);
    applicationInterface.sendDartsTournamentData.disconnect(handleFTPTournamentMetaData);
    dartsSingleAttemptBody.requestStart.disconnect(applicationInterface.handleRequestStart);
    dartsSingleAttemptBody.requestStop.disconnect(applicationInterface.handleRequestStop);
    dartsSingleAttemptBody.requestRestart.disconnect(applicationInterface.handleRestartTournament);
    dartsSingleAttemptBody.sendInput.disconnect(applicationInterface.handleSingleAttemptPlayerPointInput);
    dartsSingleAttemptBody.requestStatusFromBackend.disconnect(applicationInterface.handleControllerStateRequest);
    applicationInterface.dartsControllerRemovedSingleAttemptPoint.disconnect(backendRemovedPoint);
    dartsSingleAttemptBody.requestUndo.disconnect(applicationInterface.handleUndoRequest);
    dartsSingleAttemptBody.requestRedo.disconnect(applicationInterface.handleRedoRequest);
    pointKeyPad.sendInput.disconnect(handlePointKeyPadInput);
    applicationInterface.controllerAwaitsInput.disconnect(backendIsReadyAndAwaitsInput);
    applicationInterface.dartsControllerAddedAndPersistedScore.disconnect(extractPointScoreFromJson);
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
    singleAttemptScoreBoard.appendHeaderData(assignedPlayerNames,keyPoint);
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
        var playerScore = entity["score"];
        var playerPoint = entity["point"];
        singleAttemptScoreBoard.setData(playerName,playerPoint,playerScore);
    }
    dartsSingleAttemptBody.requestStatusFromBackend();
}

// When backend has evaluated and persisted player input
function extractPointScoreFromJson(data)
{
    var json = JSON.parse(data);
    let playerName = json["playerName"];
    let pointValue = json["point"];
    let scoreValue = json["score"];
    singleAttemptScoreBoard.setData(playerName,pointValue,scoreValue);
    requestStatusFromBackend();
}

function reinitialize()
{
    // reinitialize controller after reset
    singleAttemptScoreBoard.clearData();
    initializeScoreBoard();
    requestStatusFromBackend();
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
    singleAttemptScoreBoard.takeData(playerName);
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
    singleAttemptTurnController.updateState(currentRoundIndex,
                                            currentPlayerUserName,
                                            canUndo,
                                            canRedo);
    dartsSingleAttemptBody.state = "waitingForInput";
}

function handlePointKeyPadInput(value,keyCode){
    dartsSingleAttemptBody.state = "waitingForInputConfirmation";
    var obj = {
        point : value,
        modKeyCode : keyCode
    };
    var json = JSON.stringify(obj);
    dartsSingleAttemptBody.sendInput(json);
}

function backendIsStopped()
{
    if(dartsSingleAttemptBody.state !== "preRestart")
        dartsSingleAttemptBody.state = "stopped";
}

function backendIsInitialized()
{
    dartsSingleAttemptBody.state = "ready";
}

function backendDeclaredAWinner(data)
{
    var json = JSON.parse(data);
    tournamentMetaData.determinedWinner = json.winner;
    dartsSingleAttemptBody.state = "winner";
}

function undoClicked()
{
    dartsSingleAttemptBody.state = "waitingForInputConfirmation";
    requestUndo();
}

function redoClicked()
{
    dartsSingleAttemptBody.state = "waitingForInputConfirmation";
    requestRedo();
}

