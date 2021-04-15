function stateChanged()
{
    var selectedIndexes = playersListView.currentIndexes();
    var selectedIndexesLength = selectedIndexes.length;
    var tournamentTitle = titleEdit.currentValue;
    var tournamentTitleLength = tournamentTitle.length;
    var status = selectedIndexesLength > 0 && tournamentTitleLength > 0;
    buttonsComponent.buttonTwoEnabled = status;
}

function recievePlayers(players)
{
    for(var i=0;i < players.length;i += 2)
    {
        var playerName = players[i];
        var email = players[i+1];
        playersListView.addItemModel({"type" : "player","username" : playerName, "mail" : email})
    }
}

function gameModeToHex(text)
{
    var gameModes = gameModeSelector.model;
    if(text === gameModes[0])
        return 0x1;
}

function setupSelectors(){
    var value = gameModeSelector.currentValue;
    var mode = gameModeToHex(value);
    if(mode === TournamentContext.firstToPost)
        selectorLoader.sourceComponent = createFTPSelectors();
}

function createFTPSelectors(){
    var ftpSelectors = Qt.createComponent("FTPSelectors.qml");
    return ftpSelectors;
}

function acceptAndAdd(){
    var gameModeString = gameModeSelector.currentValue;
    var gameMode = gameModeToHex(gameModeString);
    if(gameMode === 0x1)
        assembleAndSendFTPTournament();
}

function assembleAndSendFTPTournament()
{
    var indexes = playersListView.currentIndexes();
    if(indexes.length <= 0)
        return;
    buttonsComponent.buttonTwoEnabled = false;
    var gameMode = gameModeToHex(gameModeSelector.currentValue);
    var obj = {
        Title : titleEdit.currentValue,
        GameMode : gameMode,
        Attempts : selectorComponent().attempts,
        KeyPoint : selectorComponent().keyPoint,
        TerminalKeyCode : selectorComponent().conditionKeyCode,
        DisplayHint : selectorComponent().displayHint,
        InputHint : selectorComponent().inputMode,
        PlayerIndexes : indexes
    };
    var json = JSON.stringify(obj);
    // Send values
    createBody.sendFTPDetails(json);
}
