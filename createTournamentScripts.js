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
    var title = titleEdit.currentValue;
    // Declare array
    var arguments = [];
    // Convert values
    var gameMode = gameModeSelector.currentValue;
    var attempts = selectorComponent().numberOfThrows;
    var keyPoint = selectorComponent().keyPoint;
    var winConditionKeyIdentifier = selectorComponent().conditionKeyCode;
    var displayHintSelectorValue = selectorComponent().displayHint;
    var inputModeSelectorValue = selectorComponent().inputMode;
    // Add values to array
    arguments[0] = gameModeToHex(gameMode);
    arguments[1] = keyPoint;
    arguments[2] = winConditionKeyIdentifier;
    arguments[3] = displayHintSelectorValue;
    arguments[4] = inputModeSelectorValue;
    arguments[5] = attempts;
    // Send values
    createBody.sendFTPDetails(title,
                              arguments,
                              indexes);
}
