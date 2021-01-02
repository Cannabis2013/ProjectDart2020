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
            GamePageFactory.buildKeyPad(TournamentContext.firstToPost);
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
    body.scoreRecieved.connect(scoreBoardItemSlot.item.setData);
    var assignedPlayers = currentTournamentMetaData.assignedPlayers;
    var keyPoint = currentTournamentMetaData.tournamentKeyPoint;
    scoreBoardItemSlot.item.appendHeaderData(assignedPlayers,keyPoint);
}
/*
  TurnControlle related
    - Setup TurnController
    - Handle TurnController events
  */
function setupTurnController(){
    turnControllerItemSlot.item.startButtonPressAndHoldClicked.connect(handleStartPressAndHold);
    turnControllerItemSlot.item.startButtonClicked.connect(handleStartClicked);
    turnControllerItemSlot.item.leftButtonClicked.connect(leftButtonClicked);
    turnControllerItemSlot.item.rightButtonClicked.connect(rightButtonClicked);
}
function setupKeyPad(){
    keyPaditemSlot.item.sendInput.connect(GameGeneralScripts.handleKeyPadInput);
    keyPaditemSlot.item.sendInput.connect(body.notifyUserInputRecieved);
}

function handleStartPressAndHold()
{
    if(body.state === "waitingForInput")
        body.state = "preRestart";
    else if(body.state === "stopped")
        body.state = "preRestart";
    else if(body.state === "ready")
        body.state = "preRestart";
    else if(body.state === "winner")
        body.state = "preRestart";
    else if(body.state === "preRestart")
        body.state = "ready";
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
        body.state = "restart";
    }
    else
    {
        body.state = "pauseState";
        requestStop();
    }
}

function leftButtonClicked()
{
    body.state = "waitingForInputConfirmation";
    requestUndo();
}

function rightButtonClicked()
{
    body.state = "waitingForInputConfirmation";
    requestRedo();
}
