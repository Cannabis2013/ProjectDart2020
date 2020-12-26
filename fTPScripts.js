function setupFirstToPost(){
    /*
      Load and setup turncontroller
      */
    turnControllerItemSlot.sourceComponent =
            GamePageFactory.buildTurnController(TournamentContext.firstToPost,
                                                TournamentContext.singleDimensional);
    setupTurnController();
    /*
      Load and setup DisplayKeyDataItem
      */
    notificationItemSlot.sourceComponent =
            GamePageFactory.buildDisplayItem(TournamentContext.firstToPost,
                                             TournamentContext.singleDimensional);
    /*
      Load and setup ScoreTable
      */
    scoreBoardItemSlot.sourceComponent =
            GamePageFactory.buildScoreBoard(TournamentContext.firstToPost,
                                            TournamentContext.singleDimensional);
    setupFirstToPostScoreTable();
    /*
      Load and setup DefaultKeyPadComponent
      */
    keyPaditemSlot.sourceComponent =
            GamePageFactory.buildKeyPad(TournamentContext.firstToPost,
                                        TournamentContext.singleDimensional);
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
    scoreBoardItemSlot.item.displayPoints = false;
    setupHorizontalBoard();
}

function setupVerticalBoard()
{
    scoreBoardItemSlot.item.verticalHeaderFillMode = 0x2;
    scoreBoardItemSlot.item.horizontalHeaderFillMode = 0x1;
    scoreBoardItemSlot.item.headerOrientation = Qt.Vertical;
    scoreBoardItemSlot.item.sizeScale(2);

    var assignedPlayers = currentTournamentMetaData.assignedPlayers;
    var keyPoint = currentTournamentMetaData.tournamentKeyPoint;

    for(var i = 0; i < assignedPlayers.length;i++)
    {
        var assignedPlayerName = assignedPlayers[i];
        scoreBoardItemSlot.item.appendHeader(assignedPlayerName,Qt.Vertical);
        scoreBoardItemSlot.item.setData(assignedPlayerName,0,keyPoint,undefined);
    }
}

function setupHorizontalBoard()
{
    scoreBoardItemSlot.item.verticalHeaderFillMode = 0x1;
    scoreBoardItemSlot.item.horizontalHeaderFillMode = 0x2;
    scoreBoardItemSlot.item.headerOrientation = Qt.Horizontal;
    scoreBoardItemSlot.item.sizeScale(1);
    scoreBoardItemSlot.item.verticalHeaderVisible = false;
    var assignedPlayers = currentTournamentMetaData.assignedPlayers;
    var keyPoint = currentTournamentMetaData.tournamentKeyPoint;
    for(var i = 0; i < assignedPlayers.length;i++)
    {
        var assignedPlayerName = assignedPlayers[i];
        scoreBoardItemSlot.item.appendHeader(assignedPlayerName,Qt.Horizontal);
        scoreBoardItemSlot.item.setData(assignedPlayerName,0,keyPoint,undefined);
    }
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
