function init()
{
    CreateScripts.setupSelectors();
    CreateScripts.updatePlayersView();
}
function stateChanged()
{
    var selectedIndexes = playersListView.selectedIndexes();
    var selectedIndexesLength = selectedIndexes.length;
    var tournamentTitle = titleEdit.currentValue;
    var tournamentTitleLength = tournamentTitle.length;
    buttonsComponent.buttonTwoEnabled = tournamentTitleLength > 0 && selectedIndexesLength > 0;
}
function updatePlayersView()
{
    let bytes = playersContext.players();
    var j = JSON.parse(bytes);
    for(var i=0;i < j.length;i++)
    {
        var obj = j[i];
        var playerName = obj["name"];
        var email = obj["mail"];
        playersListView.addItem(createItem(playerName,email));
    }
}
function createItem(playerName,mail)
{
    return {"type" : "player","username" : playerName, "mail" : mail}
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
        createDarts();
}

function createDarts()
{
    var indexes = playersListView.selectedIndexes();
    var json = createDartsJson(indexes);
    var result = dartsContext.addTournament(json,indexes);
    if(result)
        tournamentCreatedSucces();
    else
        tournamentCreatedFailed();
}

function createDartsJson(indexes)
{
    buttonsComponent.buttonTwoEnabled = false;
    var gameMode = gameModeToHex(gameModeSelector.currentValue);
    var obj = {
        title : titleEdit.currentValue,
        gameMode : gameMode,
        initRemScore : selectorComponent().keyPoint,
        inputHint : selectorComponent().inputMode,
        playerIndexes : indexes
    };
    return JSON.stringify(obj);
}

function tournamentCreatedSucces()
{
    createBody.requestQuit();
}

function tournamentCreatedFailed()
{
    buttonsComponent.buttonOneEnabled = true;
    buttonsComponent.buttonTwoEnabled = true;
}
