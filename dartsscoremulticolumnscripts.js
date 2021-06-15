function initializeComponent()
{
    connectInterface();
    requestControllerValues();
}

function connectInterface()
{
    dartsScoreSingleColumnBody.requestControllerValues.connect(applicationInterface.assembleDartsTournamentValues);
    dartsScoreSingleColumnBody.requestMultiAttemptScores
                         .connect(applicationInterface.handleRequestForMultiAttemptScores);
    applicationInterface.sendDartsScores.connect(recieveDartsMultiAttemptScores);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
    applicationInterface.dartsScoreControllerIsReady
                        .connect(controllerIsInitializedAndReady);
    applicationInterface.controllerHasDeclaredAWinner.connect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.sendDartsTournamentData.connect(handleFTPTournamentMetaData);
    dartsScoreSingleColumnBody.requestStart.connect(applicationInterface.handleRequestStart);
    dartsScoreSingleColumnBody.requestStop.connect(applicationInterface.handleRequestStop);
    dartsScoreSingleColumnBody.requestRestart.connect(applicationInterface.handleRestartTournament);
    dartsScoreSingleColumnBody.sendInput.connect(applicationInterface.handleDartsScoreInput);
    dartsScoreSingleColumnBody.requestStatusFromBackend.connect(applicationInterface.handleControllerStateRequest);
    applicationInterface.dartsControllerRemovedScore.connect(backendRemovedPoint);
    dartsScoreSingleColumnBody.requestUndo.connect(applicationInterface.handleDartsUndoRequest);
    dartsScoreSingleColumnBody.requestRedo.connect(applicationInterface.handleDartsRedoRequest);
    scoreKeyPad.sendInput.connect(handleScoreKeyPadInput);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
    applicationInterface.addedDartsScore.connect(extractScoreFromJson);
}

function disconnectInterface()
{
    dartsScoreSingleColumnBody.requestMultiAttemptScores.disconnect(applicationInterface.assembleDartsTournamentValues);
    dartsScoreSingleColumnBody.requestMultiAttemptScores.disconnect(
                applicationInterface.handleRequestForMultiAttemptScores);
    applicationInterface.sendDartsScores.disconnect(
                recieveDartsMultiAttemptScores);
    applicationInterface.dartsScoreControllerIsReady
                        .disconnect(controllerIsInitializedAndReady);
    applicationInterface.controllerHasDeclaredAWinner.disconnect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.disconnect(backendIsStopped);
    applicationInterface.sendDartsTournamentData.disconnect(handleFTPTournamentMetaData);
    dartsScoreSingleColumnBody.requestStart.disconnect(applicationInterface.handleRequestStart);
    dartsScoreSingleColumnBody.requestStop.disconnect(applicationInterface.handleRequestStop);
    dartsScoreSingleColumnBody.requestRestart.disconnect(applicationInterface.handleRestartTournament);
    dartsScoreSingleColumnBody.sendInput.disconnect(applicationInterface.handleDartsScoreInput);
    dartsScoreSingleColumnBody.requestStatusFromBackend.disconnect(applicationInterface.handleControllerStateRequest);
    applicationInterface.dartsControllerRemovedScore.disconnect(backendRemovedPoint);
    dartsScoreSingleColumnBody.requestUndo.disconnect(applicationInterface.handleDartsUndoRequest);
    dartsScoreSingleColumnBody.requestRedo.disconnect(applicationInterface.handleDartsRedoRequest);
    scoreKeyPad.sendInput.disconnect(handleScoreKeyPadInput);
    applicationInterface.controllerAwaitsInput.disconnect(backendIsReadyAndAwaitsInput);
    applicationInterface.addedDartsScore.disconnect(extractScoreFromJson);
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
    dartsScoreSingleColumnBody.state = "ready";
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
    dartsScoreSingleColumnBody.requestStatusFromBackend();
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
    if(dartsScoreSingleColumnBody.state === "ready")
        dartsScoreSingleColumnBody.state = "stopped";
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
    dartsScoreSingleColumnBody.state = "waitingForInput";
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
    dartsScoreSingleColumnBody.state = "waitingForInputConfirmation";
    var obj = {
        score : value
    };
    var json = JSON.stringify(obj);
    dartsScoreSingleColumnBody.sendInput(json);
}

function backendIsStopped()
{
    if(dartsScoreSingleColumnBody.state !== "preRestart")
        dartsScoreSingleColumnBody.state = "stopped";
}

function backendDeclaredAWinner(data)
{
    var json = JSON.parse(data);
    dartsMultiAttemptValues.winnerName = json.playerName;
    dartsScoreSingleColumnBody.state = "winner";
}

function undoClicked()
{
    dartsScoreSingleColumnBody.state = "waitingForInputConfirmation";
    requestUndo();
}

function redoClicked()
{
    dartsScoreSingleColumnBody.state = "waitingForInputConfirmation";
    requestRedo();
}

function setWinnerText()
{
    keyDataDisplay.setCurrentWinner(dartsMultiAttemptValues.winnerName);
}
