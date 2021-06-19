function initializeComponent()
{
    connectInterface();
    requestControllerValues();
}

function connectInterface()
{
    // Initializing ui values
    dartsPointSingleColumnBody.requestControllerValues.connect(applicationInterface.assembleDartsTournamentValues);
    dartsPointSingleColumnBody.requestMultiAttemptScores
                         .connect(applicationInterface.handleRequestForDartsSingleAttemptPoints);
    applicationInterface.sendDartsPoints.connect(recieveDartsPoints);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
    applicationInterface.dartsPointControllerIsReady
                        .connect(controllerIsInitializedAndReady);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
    applicationInterface.controllerHasDeclaredAWinner.connect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.sendDartsTournamentData.connect(handleDartsTournamentMetaData);
    dartsPointSingleColumnBody.requestStatusFromBackend.connect(applicationInterface.handleControllerStateRequest);
    dartsPointSingleColumnBody.requestStart.connect(applicationInterface.handleRequestStart);
    dartsPointSingleColumnBody.requestStop.connect(applicationInterface.handleRequestStop);
    dartsPointSingleColumnBody.requestUndo.connect(applicationInterface.handleDartsUndoRequest);
    dartsPointSingleColumnBody.requestRedo.connect(applicationInterface.handleDartsRedoRequest);
    dartsPointSingleColumnBody.requestRestart.connect(applicationInterface.handleRestartTournament);
    dartsPointSingleColumnBody.sendInput.connect(applicationInterface.handleDartsPointInput);
    applicationInterface.dartsControllerRemovedPoint.connect(backendRemovedPoint);
    pointKeyPad.sendInput.connect(handleScoreKeyPadInput);
    applicationInterface.addedDartsPoint.connect(extractPointFromJson);
}

function disconnectInterface()
{
    dartsPointSingleColumnBody.requestMultiAttemptScores.disconnect(applicationInterface.assembleDartsTournamentValues);
    dartsPointSingleColumnBody.requestMultiAttemptScores.disconnect(
                applicationInterface.handleRequestForDartsSingleAttemptPoints);
    applicationInterface.sendDartsPoints.disconnect(
                recieveDartsPoints);
    applicationInterface.dartsScoreControllerIsReady
                        .disconnect(controllerIsInitializedAndReady);
    applicationInterface.controllerHasDeclaredAWinner.disconnect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.disconnect(backendIsStopped);
    applicationInterface.sendDartsTournamentData.disconnect(handleDartsTournamentMetaData);
    dartsPointSingleColumnBody.requestStart.disconnect(applicationInterface.handleRequestStart);
    dartsPointSingleColumnBody.requestStop.disconnect(applicationInterface.handleRequestStop);
    dartsPointSingleColumnBody.requestRestart.disconnect(applicationInterface.handleRestartTournament);
    dartsPointSingleColumnBody.sendInput.disconnect(applicationInterface.handleDartsPointInput);
    dartsPointSingleColumnBody.requestStatusFromBackend.disconnect(applicationInterface.handleControllerStateRequest);
    applicationInterface.dartsControllerRemovedScore.disconnect(backendRemovedPoint);
    dartsPointSingleColumnBody.requestUndo.disconnect(applicationInterface.handleDartsUndoRequest);
    dartsPointSingleColumnBody.requestRedo.disconnect(applicationInterface.handleDartsRedoRequest);
    pointKeyPad.sendInput.disconnect(handleScoreKeyPadInput);
    applicationInterface.controllerAwaitsInput.disconnect(backendIsReadyAndAwaitsInput);
    applicationInterface.addedDartsScore.disconnect(extractPointFromJson);
}

function handleDartsTournamentMetaData(data){
    var json = JSON.parse(data);
    dartsPointSingleColumnMetaValues.title = json["title"];
    dartsPointSingleColumnMetaValues.winnerName= json["winnerName"];
    dartsPointSingleColumnMetaValues.keyPoint = json["keyPoint"];
    dartsPointSingleColumnMetaValues.attempts = json["attempts"];
    dartsPointSingleColumnMetaValues.assignedPlayerNames = json["assignedPlayerNames"];
    initializeScoreBoard();
    requestMultiAttemptScores();
}

function initializeScoreBoard()
{
    var assignedPlayerNames = dartsPointSingleColumnMetaValues.assignedPlayerNames;
    var keyPoint = dartsPointSingleColumnMetaValues.keyPoint;
    singleColumnPointBoard.appendHeaderData(assignedPlayerNames,keyPoint);
}

function controllerIsInitializedAndReady()
{
    dartsPointSingleColumnBody.state = "ready";
}

function recieveDartsPoints(points)
{
    var jsonData = JSON.parse(points);
    var count = jsonData.length;
    for(var i = 0;i < count;++i)
    {
        var entity = jsonData[i];
        var playerName = entity["playerName"];
        var playerPoint = entity["point"];
        var totalScore = entity["totalScore"];
        singleColumnPointBoard.setData(playerName,playerPoint,totalScore);
    }
    dartsPointSingleColumnBody.requestStatusFromBackend();
}

// When backend has evaluated and persisted player input
function extractPointFromJson(data)
{
    var json = JSON.parse(data);
    let playerName = json["playerName"];
    let playerPoint = json["point"];
    let totalScore = json["totalScore"];
    singleColumnPointBoard.setData(playerName,playerPoint,totalScore);
    requestStatusFromBackend();
}

function reinitialize()
{
    singleColumnPointBoard.clearData();
    pointSingleColumnTurnController.backendIsStopped();
    keyDataDisplay.clear();
    initializeScoreBoard();
    requestStatusFromBackend();
}

function handleRequestTournamentReset()
{
    if(dartsPointSingleColumnBody.state === "ready")
        dartsPointSingleColumnBody.state = "stopped";
}

function backendRemovedPoint(data)
{
    var json = JSON.parse(data);
    let playerName = json["playerName"];
    let playerPoint = json["point"];
    let score = json["totalScore"];
    singleColumnPointBoard.setData(playerName,playerPoint,score);
    requestStatusFromBackend();
}

function backendIsReadyAndAwaitsInput(data)
{
    var json = JSON.parse(data);
    let throwSuggestion = json.targetRow;
    keyDataDisplay.setThrowSuggestion(throwSuggestion);
    dartsPointSingleColumnBody.state = "waitingForInput";
    setTurnControllerValues(json);
}

function setTurnControllerValues(json)
{
    pointSingleColumnTurnController.leftButtonEnabled = json.canUndo;
    pointSingleColumnTurnController.rightButtonEnabled = json.canRedo;
    pointSingleColumnTurnController.currentRoundIndex = json.roundIndex;
    pointSingleColumnTurnController.currentPlayer = json.playerName;
}

function handleScoreKeyPadInput(input, keyCode){
    dartsPointSingleColumnBody.state = "waitingForInputConfirmation";
    var obj = {
        point : input,
        modKeyCode : keyCode
    };
    var json = JSON.stringify(obj);
    dartsPointSingleColumnBody.sendInput(json);
}

function backendIsStopped()
{
    if(dartsPointSingleColumnBody.state !== "preRestart")
        dartsPointSingleColumnBody.state = "stopped";
}

function backendDeclaredAWinner(data)
{
    var json = JSON.parse(data);
    dartsPointSingleColumnMetaValues.winnerName = json.playerName;
    dartsPointSingleColumnBody.state = "winner";
}

function undoClicked()
{
    dartsPointSingleColumnBody.state = "waitingForInputConfirmation";
    requestUndo();
}

function redoClicked()
{
    dartsPointSingleColumnBody.state = "waitingForInputConfirmation";
    requestRedo();
}

function setWinnerText()
{
    keyDataDisplay.setCurrentWinner(dartsPointSingleColumnMetaValues.winnerName);
}
