function buildFtpComponents(){
    /*
      Load and setup turncontroller
      */
    turnControllerItemSlot.sourceComponent =
            GamePageFactory.buildTurnController(TournamentContext.firstToPost);
    /*
      Load and setup ScoreTable
      */
    scoreBoardItemSlot.sourceComponent =
            GamePageFactory.buildFTPScoreBoard(tournamentMetaData.tournamentTableViewHint);
    /*
      Load and setup DisplayKeyDataItem
      */
    notificationItemSlot.sourceComponent =
            GamePageFactory.buildDisplayItem(TournamentContext.firstToPost);
    /*
      Load and setup DefaultKeyPadComponent
      */
    keyPaditemSlot.sourceComponent =
            GamePageFactory.buildKeyPad(tournamentMetaData.tournamentInputMode);
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
    var hint = tournamentMetaData.tournamentTableViewHint;
    if(hint === DataModelContext.singleAttempt)
        requestSingleThrowScores();
    else if(hint === DataModelContext.multiAttempt);
        configureMultiScoreBoard();
}

function reinitialize()
{
    let keyPoint = tournamentMetaData.tournamentKeyPoint;
    let names = tournamentMetaData.assignedPlayers;
    for(var i = 0;i < names.length;i++)
    {
        let name = names[i];
        appendScore(name,0,keyPoint,-1);
    }
    disconnectFtpInterface();
    buildFtpComponents();
}

function setupWindowTitle()
{
    var title = tournamentMetaData.tournamentTitle;
    requestSetPageTitle(title);
}

function connectFtpInterface()
{
    applicationInterface.ftpControllerRemovedScore.connect(backendRemovedScore);
    applicationInterface.ftpControllerAddedAndPersistedScore.connect(backendAddedAndPersistedScore);
    applicationInterface.ftpControllerIsReset.connect(reinitialize);
    keyPadInterface().sendInput.connect(GameGeneralScripts.handleKeyPadInput);
    gamePageBody.scoreRecieved.connect(scoreBoardItemSlot.item.setData);
    applicationInterface.sendAssembledMultiFtpScores.connect(recieveFtpMultiAttemptScores);
    gamePageBody.requestSingleThrowScores.connect(applicationInterface.handleRequestForSingleThrowScoreData);
    gamePageBody.requestMultiThrowScores.connect(applicationInterface.handleRequestForMultiThrowScoreData);
    applicationInterface.sendAssembledSingleFtpScores.connect(recieveFtpSingleAttemptScores);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
}
function disconnectFtpInterface()
{
    applicationInterface.ftpControllerRemovedScore.disconnect(backendRemovedScore);
    applicationInterface.ftpControllerAddedAndPersistedScore.disconnect(backendAddedAndPersistedScore);
    applicationInterface.ftpControllerIsReset.disconnect(reinitialize);
    keyPadInterface().sendInput.disconnect(GameGeneralScripts.handleKeyPadInput);
    gamePageBody.scoreRecieved.disconnect(scoreBoardItemSlot.item.setData);
    applicationInterface.sendAssembledMultiFtpScores.disconnect(recieveFtpMultiAttemptScores);
    gamePageBody.requestSingleThrowScores.disconnect(applicationInterface.handleRequestForSingleThrowScoreData);
    gamePageBody.requestMultiThrowScores.disconnect(applicationInterface.handleRequestForMultiThrowScoreData);
    applicationInterface.sendAssembledSingleFtpScores.disconnect(recieveFtpSingleAttemptScores);
    applicationInterface.controllerAwaitsInput.disconnect(backendIsReadyAndAwaitsInput);
}

function configureMultiScoreBoard()
{
    if(tournamentMetaData.tournamentInputMode === TournamentContext.scoreMode)
        scoreBoardInterface().attempts = tournamentMetaData.attempts;
    requestMultiThrowScores();
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
        gamePageBody.scoreRecieved(playerName,playerPoint,playerScore,keyCode);
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
        gamePageBody.scoreRecieved(playerName,0,playerScore,-1);
    }
    gamePageBody.requestStatusFromBackend();
}

function backendAddedAndPersistedScore(data)
{
    var json = JSON.parse(data);
    let playerName = json["playerName"];
    let pointValue = json["point"];
    let scoreValue = json["accumulatedScoreValue"];
    let keyCode = json["modKeyCode"];
    appendScore(playerName,pointValue,scoreValue,keyCode);
    requestStatusFromBackend();
}
function backendRemovedScore(data)
{
    var json = JSON.parse(data);
    let playerName = json["playerName"];
    let scoreValue = json["playerScore"];
    let pointValue = json["playerPoint"];
    alterScore(playerName,scoreValue,pointValue);
    requestStatusFromBackend();
}
function appendScore(player,point,score,keyCode)
{
    gamePageBody.scoreRecieved(player,point,score,keyCode);
}
function alterScore(player,score,point)
{
    if(tournamentMetaData.tournamentGameMode === TournamentContext.firstToPost)
    {
        if(tournamentMetaData.tournamentTableViewHint === DataModelContext.singleAttempt)
            scoreBoardInterface().setData(player,point,score,-1);
        else if(tournamentMetaData.tournamentTableViewHint === DataModelContext.multiAttempt)
            scoreBoardInterface().takeData(-1,-1,player);
    }
}




