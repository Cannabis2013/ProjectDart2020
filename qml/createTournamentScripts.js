function init()
{
    connect();
    CreateScripts.setupSelectors();
    CreateScripts.updatePlayersView();
}
function connect()
{
    dartsContext.tournamentCreatedOk.connect(createBody.requestQuit);
    dartsContext.tournamentCreatedFail.connect(tournamentCreatedFailed);
}

function disconnect()
{
    dartsContext.tournamentCreatedOk.disconnect(requestQuit);
    dartsContext.tournamentCreatedFail.disconnect(tournamentCreatedFailed);
}
function stateChanged()
{
    var selectedIndexes = playersListView.currentIndexes;
    var selectedIndexesLength = selectedIndexes.length;
    var tournamentTitle = titleEdit.currentValue;
    var tournamentTitleLength = tournamentTitle.length;
    buttonsComponent.buttonTwoEnabled = tournamentTitleLength > 0 && selectedIndexesLength > 0;
}
function updatePlayersView()
{
    let bytes = playersContext.playerModels();
    var j = JSON.parse(bytes);
    for(var i=0;i < j.length;i++)
    {
        var obj = j[i];
        var playerName = obj["playerName"];
        var email = obj["playerMail"];
        playersListView.addItem({"type" : "player","username" : playerName, "mail" : email});
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
        selectorLoader.sourceComponent = createDartsSelectors();
}
function createDartsSelectors(){
    var dartsSelectors = Qt.createComponent("DartsTournamentSelectors.qml");
    return dartsSelectors;
}
function acceptAndAdd(){
    var gameModeString = gameModeSelector.currentValue;
    var gameMode = gameModeToHex(gameModeString);
    if(gameMode === 0x1)
        createDartsTournament();
}
function createDartsTournament()
{
    var indexes = playersListView.currentIndexes;
    if(indexes.length <= 0)
        return;
    buttonsComponent.buttonTwoEnabled = false;
    var gameMode = gameModeToHex(gameModeSelector.currentValue);
    var obj = {
        title : titleEdit.currentValue,
        gameMode : gameMode,
        keyPoint : selectorComponent().keyPoint,
        inputHint : selectorComponent().inputMode,
        playerIndexes : indexes
    };
    var json = JSON.stringify(obj);
    dartsContext.addTournament(json,indexes);
}
function tournamentCreatedFailed()
{
    buttonsComponent.buttonOneEnabled = true;
    buttonsComponent.buttonTwoEnabled = true;
}
