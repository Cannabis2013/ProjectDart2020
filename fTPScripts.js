function setupFirstToPost(){
    /*
      Load and setup turncontroller
      */
    turnControllerItemSlot.sourceComponent =
            GamePageFactory.buildTurnController(TournamentContext.firstToPost);
    setupTurnController();
    /*
      Load and setup ScoreTable
      */
    scoreBoardItemSlot.sourceComponent =
            GamePageFactory.buildScoreBoard(TournamentContext.firstToPost,
                                            tournamentMetaData.tournamentTableViewHint);
    setupFirstToPostScoreTable();
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
    setupKeyPad();
    initializeFirstToPost();
}

function initializeFirstToPost()
{
    // Connect
    gamePageBody.requestSingleThrowScores.connect(applicationInterface.handleRequestForSingleThrowScoreData);
    gamePageBody.requestMultiThrowScores.connect(applicationInterface.handleRequestForMultiThrowScoreData);
    var title = tournamentMetaData.tournamentTitle;
    requestSetPageTitle(title);
    var hint = tournamentMetaData.tournamentTableViewHint;
    if(hint === DataModelContext.singleAttempt)
        requestSingleThrowScores();
    else if(hint === DataModelContext.multiAttempt);
        configureMultiScoreBoard();

}

function configureMultiScoreBoard()
{
    if(tournamentMetaData.tournamentInputMode === TournamentContext.scoreMode)
        scoreBoardInterface().attempts = 1;

    requestMultiThrowScores();
}

function setupFirstToPostScoreTable()
{
    gamePageBody.scoreRecieved.connect(scoreBoardItemSlot.item.setData);
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
    turnControllerInterface().startButtonPressAndHoldClicked.connect(handleStartPressAndHold);
    turnControllerInterface().startButtonClicked.connect(handleStartClicked);
    turnControllerInterface().quitButtonClicked.connect(requestPersistState);
    turnControllerInterface().leftButtonClicked.connect(leftButtonClicked);
    turnControllerInterface().rightButtonClicked.connect(rightButtonClicked);
}
function setupKeyPad(){
    keyPadInterface().sendInput.connect(GameGeneralScripts.handleKeyPadInput);
}

function handleStartPressAndHold()
{
    if(gamePageBody.state === "waitingForInput")
        gamePageBody.state = "preRestart";
    else if(gamePageBody.state === "stopped")
        gamePageBody.state = "preRestart";
    else if(gamePageBody.state === "ready")
        gamePageBody.state = "preRestart";
    else if(gamePageBody.state === "winner")
        gamePageBody.state = "preRestart";
    else if(gamePageBody.state === "preRestart")
        gamePageBody.state = "ready";
}
function handleStartClicked()
{
    var buttonText = turnControllerItemSlot.item.startButtonText;
    if(buttonText === buttonTextContainer.startText ||
            buttonText === buttonTextContainer.resumeText)
    {
        requestStart();
    }
    else if(buttonText === buttonTextContainer.restartText)
    {
        gamePageBody.requestRestart();
    }
    else
    {
        gamePageBody.state = "pauseState";
        requestStop();
    }
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
