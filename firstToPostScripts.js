function createAndSetupFirstToPostComponents(){
    /*
      Load and setup turncontroller
      */
    turnControllerItemSlot.sourceComponent = Qt.createComponent("FirstToPostTurnController.qml");
    turnControllerItemSlot.item.startButtonPressAndHoldClicked.connect(GameGeneralScripts.handleStartPressAndHold);
    turnControllerItemSlot.item.startButtonClicked.connect(GameGeneralScripts.handleStartClicked);
    /*
      Load and setup DisplayKeyDataItem
      */
    notificationItemSlot.sourceComponent = Qt.createComponent("DisplayKeyDataItem.qml");
    /*
      Load and setup ScoreTable
      */
    scoreBoardItemSlot.sourceComponent = Qt.createComponent("FirstToPostTable.qml");
    setupFirstToPostScoreTable()
    /*
      Load and setup DefaultKeyPadComponent
      */
    keyPaditemSlot.sourceComponent = Qt.createComponent("DefaultKeyPadComponent.qml");
    keyPaditemSlot.item.sendInput.connect(GameGeneralScripts.handleKeyPadInput);
}

function initializeFirstToPost()
{
    var title = currentTournamentMetaData.tournamentTitle;
    requestSetPageTitle(title);
    requestScoreBoardData();
}
function setupFirstToPostScoreTable()
{
    body.scoreRecieved.connect(scoreBoardItemSlot.item.appendData);
    var assignedPlayers = currentTournamentMetaData.assignedPlayers;
    var keyPoint = currentTournamentMetaData.tournamentKeyPoint;
    for(var i = 0; i < assignedPlayers.length;i++)
    {
        var assignedPlayerName = assignedPlayers[i];
        scoreBoardItemSlot.item.appendHeader(assignedPlayerName);
        scoreBoardItemSlot.item.appendData(assignedPlayerName,0,keyPoint,undefined);
    }
    scoreBoardItemSlot.item.displayPoints = true;
    scoreBoardItemSlot.item.setMinimumColumnsCount(4);
}
