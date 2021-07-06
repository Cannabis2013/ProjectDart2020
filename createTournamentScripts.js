function stateChanged()
{
    var selectedIndexes = playersListView.currentIndexes();
    var selectedIndexesLength = selectedIndexes.length;
    var tournamentTitle = titleEdit.currentValue;
    var tournamentTitleLength = tournamentTitle.length;
    var status = selectedIndexesLength > 0 && tournamentTitleLength > 0;
    buttonsComponent.buttonTwoEnabled = status;
}

function recievePlayers(data)
{
    var j = JSON.parse(data);
    for(var i=0;i < j.length;i++)
    {
        var obj = j[i];
        var playerName = obj["playerName"];
        var email = obj["playerMail"];
        playersListView.addItemModel({"type" : "player","username" : playerName, "mail" : email});
    }
}

function gameModeToHex(text)
{
    var gameModes = gameModeSelector.model;
    if(text === gameModes[0])
        return TournamentContext.darts;
}

function setupSelectors(){
    var value = gameModeSelector.currentValue;
    var mode = gameModeToHex(value);
    if(mode === TournamentContext.darts)
        selectorLoader.sourceComponent = createFTPSelectors();
}

function createFTPSelectors(){
    var ftpSelectors = Qt.createComponent("DartsTournamentSelectors.qml");
    return ftpSelectors;
}

function acceptAndAdd(){
    var gameModeString = gameModeSelector.currentValue;
    var gameMode = gameModeToHex(gameModeString);
    if(gameMode === 0x1)
        createDartsTournament();
}

function createDartsTournament()
{
    var indexes = playersListView.currentIndexes();
    if(indexes.length <= 0)
        return;
    buttonsComponent.buttonTwoEnabled = false;
    var gameMode = gameModeToHex(gameModeSelector.currentValue);
    var obj = {
        title : titleEdit.currentValue,
        gameMode : gameMode,
        attempts : selectorComponent().attempts,
        keyPoint : selectorComponent().keyPoint,
        terminalKeyCode : selectorComponent().conditionKeyCode,
        displayHint : selectorComponent().displayHint,
        inputHint : selectorComponent().inputMode,
        indexes : indexes
    };
    var json = JSON.stringify(obj);
    // Send values
    createBody.sendDartsDetails(json);
}
