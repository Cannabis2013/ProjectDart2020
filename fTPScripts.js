function buildFtpComponents(){
    /*
      Load and setup turncontroller
      */
    turnControllerItemSlot.sourceComponent =
            GamePageFactory.buildTurnController(TournamentContext.darts);
    /*
      Load and setup ScoreTable
      */
    scoreBoardItemSlot.sourceComponent =
            GamePageFactory.buildFtpScoreBoard(tournamentMetaData.displayHint,
                                               tournamentMetaData.inputHint,
                                               tournamentMetaData.attempts);
    /*
      Load and setup DisplayKeyDataItem
      */
    notificationItemSlot.sourceComponent =
            GamePageFactory.buildDisplayItem(TournamentContext.darts);
    /*
      Load and setup DefaultKeyPadComponent
      */
    keyPaditemSlot.sourceComponent =
            GamePageFactory.buildAndConnectKeyPad(tournamentMetaData.inputHint);
    initialize();
}

function initialize()
{
    // Connect interfaces
    connectFtpInterface();
    // Setup components
    setupTurnController();
    setupFirstToPostScoreTable();
    // Setup window title
    setupWindowTitle();
    // Request initial scores
    requestScoresFromBackend();
}

function reinitialize()
{
    disconnectFtpInterface();
    buildFtpComponents();
    requestScoresFromBackend();
}

function requestScoresFromBackend()
{
    var hint = tournamentMetaData.tournamentTableViewHint;
    if(hint === DataModelContext.singleAttempt)
        requestSingleThrowScores();
    else if(hint === DataModelContext.multiAttempt);
        requestMultiThrowScores();
}

function setupWindowTitle()
{
    var title = tournamentMetaData.tournamentTitle;
    requestSetPageTitle(title);
}

function connectFtpInterface()
{
    applicationInterface.ftpControllerRemovedScore.connect(backendRemovedPoint);
    applicationInterface.ftpControllerIsReset.connect(reinitialize);
    keyPadInterface().sendInput.connect(handlePointKeyPadInput);
    gamePageBody.requestUndo.connect(applicationInterface.handleUndoRequest);
    gamePageBody.requestRedo.connect(applicationInterface.handleRedoRequest);
    gamePageBody.requestSingleThrowScores.connect(applicationInterface.handleRequestForSingleThrowScoreData);
    gamePageBody.requestMultiThrowScores.connect(applicationInterface.handleRequestForMultiThrowScoreData);
    applicationInterface.sendAssembledSingleFtpScores.connect(recieveFtpSingleAttemptScores);
    applicationInterface.sendAssembledMultiFtpScores.connect(recieveFtpMultiAttemptScores);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
}
function disconnectFtpInterface()
{
    applicationInterface.ftpControllerRemovedScore.disconnect(backendRemovedPoint);
    applicationInterface.ftpControllerAddedAndPersistedScore.disconnect(extractPointScoreFromJson);
    applicationInterface.ftpControllerAddedAndPersistedScore.disconnect(extractScoreFromJson);
    applicationInterface.ftpControllerIsReset.disconnect(reinitialize);
    keyPadInterface().sendInput.disconnect(handlePointKeyPadInput);
    gamePageBody.requestUndo.disconnect(applicationInterface.requestUndo);
    gamePageBody.requestRedo.disconnect(applicationInterface.requestRedo);
    applicationInterface.sendAssembledMultiFtpScores.disconnect(recieveFtpMultiAttemptScores);
    gamePageBody.requestSingleThrowScores.disconnect(applicationInterface.handleRequestForSingleThrowScoreData);
    gamePageBody.requestMultiThrowScores.disconnect(applicationInterface.handleRequestForMultiThrowScoreData);
    applicationInterface.sendAssembledSingleFtpScores.disconnect(recieveFtpSingleAttemptScores);
    applicationInterface.controllerAwaitsInput.disconnect(backendIsReadyAndAwaitsInput);
}
function setupFirstToPostScoreTable()
{
    var assignedPlayers = tournamentMetaData.assignedPlayers;
    var keyPoint = tournamentMetaData.tournamentKeyPoint;
    scoreBoardInterface().appendHeaderData(assignedPlayers,keyPoint);
}
/*
  TurnControlle related
    - Setup TurnController
    - Handle TurnController events
  */
function setupTurnController(){
    turnControllerInterface().startButtonClicked.connect(gamePageBody.requestStart);
    turnControllerInterface().resumeButtonClicked.connect(gamePageBody.requestStart);
    turnControllerInterface().pauseButtonClicked.connect(gamePageBody.requestStop);
    turnControllerInterface().restartButtonClicked.connect(requestRestart);
    turnControllerInterface().leftButtonClicked.connect(leftButtonClicked);
    turnControllerInterface().rightButtonClicked.connect(rightButtonClicked);
}

function leftButtonClicked()
{
    gamePageBody.state = "waitingForInputConfirmation";
    requestUndo();
}

function rightButtonClicked()
{
    gamePageBody.state = "waitingForInputConfirmation";
    requestRedo();
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
    gamePageBody.notificationInterface().setThrowSuggestion(suggestion);
    gamePageBody.turnControllerInterface().updateState(currentRoundIndex,
                                            currentPlayerUserName,
                                            canUndo,
                                            canRedo);
    gamePageBody.state = "waitingForInput";
}

function recieveFtpMultiAttemptScores(scores)
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
    gamePageBody.requestStatusFromBackend();
}

function recieveFtpSingleAttemptScores(scores)
{
    var jsonData = JSON.parse(scores);
    var entities = jsonData.entities;
    var count = entities.length;
    for(var i = 0;i < count;++i)
    {
        var entity = entities[i];
        var playerName = entity.playerName;
        var playerScore = entity.playerScore;
        scoreBoardInterface().setData(playerName,playerScore);
    }
    gamePageBody.requestStatusFromBackend();
}

function extractPointScoreFromJson(data)
{
    var json = JSON.parse(data);
    let playerName = json["playerName"];
    let pointValue = json["point"];
    let scoreValue = json["accumulatedScoreValue"];
    let keyCode = json["modKeyCode"];
    scoreBoardInterface().setData(playerName,pointValue,scoreValue,keyCode);
    requestStatusFromBackend();
}
function extractScoreFromJson(data)
{
    var json = JSON.parse(data);
    var playerName = json["playerName"];
    var scoreValue = json["accumulatedScoreValue"];
    scoreBoardInterface().setData(playerName,scoreValue);
    requestStatusFromBackend();
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

function alterScore(player,score,point)
{
    if(tournamentMetaData.tournamentGameMode === TournamentContext.darts)
    {
        if(tournamentMetaData.tournamentTableViewHint === DataModelContext.singleAttempt)
            scoreBoardInterface().setData(player,point,score,-1);
        else if(tournamentMetaData.tournamentTableViewHint === DataModelContext.multiAttempt)
            scoreBoardInterface().takeData(-1,-1,player);
    }
}

/*
  Handle user input
  */
function handlePointKeyPadInput(value,keyCode){
    gamePageBody.state = "waitingForInputConfirmation";
    var obj = {
        Point : value,
        ModKeyCode : keyCode
    };
    var json = JSON.stringify(obj);
    gamePageBody.sendInput(json);
}




