function initializeComponent()
{
    connectInterface();
    requestControllerValues();
}

function connectInterface()
{
    dartsMultiAttemptBody.requestControllerValues.connect(applicationInterface.assembleDartsTournamentValues);
    dartsMultiAttemptBody.requestMultiAttemptScores
                         .connect(applicationInterface.handleRequestForMultiAttemptScores);
    applicationInterface.sendAssembledMultiAttemptDartsScores.connect(recieveDartsMultiAttemptScores);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
    applicationInterface.dartsMultiAttemptScoreControllerIsReady
                        .connect(controllerIsInitializedAndReady);
    applicationInterface.controllerHasDeclaredAWinner.connect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.sendDartsTournamentData.connect(handleFTPTournamentMetaData);
    dartsMultiAttemptBody.requestStart.connect(applicationInterface.handleRequestStart);
    dartsMultiAttemptBody.requestStop.connect(applicationInterface.handleRequestStop);
    dartsMultiAttemptBody.requestRestart.connect(applicationInterface.handleRestartTournament);
    dartsMultiAttemptBody.sendInput.connect(applicationInterface.handleDartsMultiAttemptInput);
    dartsMultiAttemptBody.requestStatusFromBackend.connect(applicationInterface.handleControllerStateRequest);
    applicationInterface.dartsControllerRemovedMultiAttemptScore.connect(backendRemovedPoint);
    dartsMultiAttemptBody.requestUndo.connect(applicationInterface.handleUndoRequest);
    dartsMultiAttemptBody.requestRedo.connect(applicationInterface.handleRedoRequest);
    scoreKeyPad.sendInput.connect(handleScoreKeyPadInput);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
    applicationInterface.dartsControllerAddedDartsMultiAttemptScore.connect(extractScoreFromJson);
}

function disconnectInterface()
{
    dartsMultiAttemptBody.requestMultiAttemptScores.disconnect(applicationInterface.assembleDartsTournamentValues);
    dartsMultiAttemptBody.requestMultiAttemptScores.disconnect(
                applicationInterface.handleRequestForMultiAttemptScores);
    applicationInterface.sendAssembledMultiAttemptDartsScores.disconnect(
                recieveDartsMultiAttemptScores);
    applicationInterface.dartsMultiAttemptScoreControllerIsReady
                        .disconnect(controllerIsInitializedAndReady);
    applicationInterface.controllerHasDeclaredAWinner.disconnect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.disconnect(backendIsStopped);
    applicationInterface.sendDartsTournamentData.disconnect(handleFTPTournamentMetaData);
    dartsMultiAttemptBody.requestStart.disconnect(applicationInterface.handleRequestStart);
    dartsMultiAttemptBody.requestStop.disconnect(applicationInterface.handleRequestStop);
    dartsMultiAttemptBody.requestRestart.disconnect(applicationInterface.handleRestartTournament);
    dartsMultiAttemptBody.sendInput.disconnect(applicationInterface.handleDartsMultiAttemptInput);
    dartsMultiAttemptBody.requestStatusFromBackend.disconnect(applicationInterface.handleControllerStateRequest);
    applicationInterface.dartsControllerRemovedMultiAttemptScore.disconnect(backendRemovedPoint);
    dartsMultiAttemptBody.requestUndo.disconnect(applicationInterface.handleUndoRequest);
    dartsMultiAttemptBody.requestRedo.disconnect(applicationInterface.handleRedoRequest);
    scoreKeyPad.sendInput.disconnect(handleScoreKeyPadInput);
    applicationInterface.controllerAwaitsInput.disconnect(backendIsReadyAndAwaitsInput);
    applicationInterface.dartsControllerAddedDartsMultiAttemptScore.disconnect(extractScoreFromJson);
}

function handleFTPTournamentMetaData(data){
    var json = JSON.parse(data);
    dartsMultiAttemptValues.title = json["title"];
    dartsMultiAttemptValues.winnerName= json["winnerName"];
    dartsMultiAttemptValues.keyPoint = json["keyPoint"];
    dartsMultiAttemptValues.attempts = json["attempts"];
    dartsMultiAttemptValues.assignedPlayerNames = json["assignedPlayerNames"];
    initializeScoreBoard();
    requestMultiAttemptScores();
}

function initializeScoreBoard()
{
    var assignedPlayerNames = dartsMultiAttemptValues.assignedPlayerNames;
    var keyPoint = dartsMultiAttemptValues.keyPoint;
    multiAttemptScoreBoard.appendHeaderData(assignedPlayerNames,keyPoint);
}

function controllerIsInitializedAndReady()
{
    dartsMultiAttemptBody.state = "ready";
}

function recieveDartsMultiAttemptScores(scores)
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
function extractScoreFromJson(data)
{
    var json = JSON.parse(data);
    let playerName = json["playerName"];
    let scoreValue = json["totalScore"];
    multiAttemptScoreBoard.setData(playerName,scoreValue);
    requestStatusFromBackend();
}

function reinitialize()
{
    multiAttemptScoreBoard.clearData();
    multiAttemptScoreTurnController.backendIsStopped();
    keyDataDisplay.clear();
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
    let score = json["totalScore"];
    multiAttemptScoreBoard.setData(playerName,score);
    requestStatusFromBackend();
}

function backendIsReadyAndAwaitsInput(data)
{
    var json = JSON.parse(data);
    let throwSuggestion = json.targetRow;
    keyDataDisplay.setThrowSuggestion(throwSuggestion);
    dartsMultiAttemptBody.state = "waitingForInput";
    setTurnControllerValues(json);
}

function setTurnControllerValues(json)
{
    multiAttemptScoreTurnController.leftButtonEnabled = json.canUndo;
    multiAttemptScoreTurnController.rightButtonEnabled = json.canRedo;
    multiAttemptScoreTurnController.currentRoundIndex = json.roundIndex;
    multiAttemptScoreTurnController.currentPlayer = json.playerName;
}

function handleScoreKeyPadInput(value){
    dartsMultiAttemptBody.state = "waitingForInputConfirmation";
    var obj = {
        score : value
    };
    var json = JSON.stringify(obj);
    dartsMultiAttemptBody.sendInput(json);
}

function backendIsStopped()
{
    if(dartsMultiAttemptBody.state !== "preRestart")
        dartsMultiAttemptBody.state = "stopped";
}

function backendDeclaredAWinner(data)
{
    var json = JSON.parse(data);
    dartsMultiAttemptValues.winnerName = json.playerName;
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

function setWinnerText()
{
    keyDataDisplay.setCurrentWinner(dartsMultiAttemptValues.winnerName);
}
