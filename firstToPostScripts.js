function setupFirstToPost(){
    /*
      Load and setup turncontroller
      */
    turnControllerItemSlot.sourceComponent = Qt.createComponent("FirstToPostTurnController.qml");
    turnControllerItemSlot.item.startButtonPressAndHoldClicked.connect(handleStartPressAndHold);
    turnControllerItemSlot.item.startButtonClicked.connect(handleStartClicked);
    turnControllerItemSlot.item.leftButtonClicked.connect(leftButtonClicked);
    turnControllerItemSlot.item.rightButtonClicked.connect(rightButtonClicked);
    /*
      Load and setup DisplayKeyDataItem
      */
    notificationItemSlot.sourceComponent = Qt.createComponent("DisplayKeyDataItem.qml");
    /*
      Load and setup ScoreTable
      */
    scoreBoardItemSlot.sourceComponent = Qt.createComponent("FirstToPostScoreBoard.qml");
    setupFirstToPostScoreTable()
    /*
      Load and setup DefaultKeyPadComponent
      */
    keyPaditemSlot.sourceComponent = Qt.createComponent("DefaultKeyPadComponent.qml");
    keyPaditemSlot.item.sendInput.connect(GameGeneralScripts.handleKeyPadInput);

    FirstToPostScripts.initializeFirstToPost();
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
    scoreBoardItemSlot.item.minimumColumnCount(4);
}

function setupHorizontalBoard()
{
    scoreBoardItemSlot.item.verticalHeaderFillMode = 0x1;
    scoreBoardItemSlot.item.horizontalHeaderFillMode = 0x2;
    scoreBoardItemSlot.item.headerOrientation = Qt.Horizontal;
    scoreBoardItemSlot.item.minimumRowCount(4);
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
  Handle TurnController events
  */
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
