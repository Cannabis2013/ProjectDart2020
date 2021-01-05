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
                                            currentTournamentMetaData.tournamentTableViewHint);
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
            GamePageFactory.buildKeyPad(TournamentContext.pointMode);
    setupKeyPad();
    initializeFirstToPost();
}

function initializeFirstToPost()
{
    var title = currentTournamentMetaData.tournamentTitle;
    requestSetPageTitle(title);
    requestScoreBoardData();
}
function setupFirstToPostScoreTable()
{
    gamePageBody.scoreRecieved.connect(scoreBoardItemSlot.item.setData);
    var assignedPlayers = currentTournamentMetaData.assignedPlayers;
    var keyPoint = currentTournamentMetaData.tournamentKeyPoint;
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
    turnControllerInterface().leftButtonClicked.connect(leftButtonClicked);
    turnControllerInterface().rightButtonClicked.connect(rightButtonClicked);
}
function setupKeyPad(){
    keyPadInterface().sendInput.connect(GameGeneralScripts.handleKeyPadInput);
    keyPadInterface().sendInput.connect(gamePageBody.notifyUserInputRecieved);
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
        gamePageBody.state = "restart";
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
