function init()
{
    updatePlayersView();
    updateTournamentsView();
}
function requestDeletePlayerPopUp()
{
    let selectedIndex = playersListView.currentIndexes;
    let count = selectedIndex.length;
    playersListView.unSelectAll();
    if(count > 0)
        PopupBuilder.createConfirmPopUp(applicationWindow,delPlayCancel,delPlayAccept);
}
function delPlayCancel()
{
    playersListView.unSelectAll();
}

function delPlayAccept(){
    var indexes = playersListView.currentIndexes;
    playersContext.remove(indexes);
}
function requestDeleteTournamentPopUp()
{
    let selectedIndexes = tournamentListView.currentIndexes;
    let count = selectedIndexes.length;
    if(count > 0)
        PopupBuilder.createConfirmPopUp(applicationWindow,deleteTournamentsCancelled,deleteTournamentsAccepted);
}
function deleteTournamentsAccepted()
{
    let indexes = tournamentListView.currentIndexes;
    dartsContext.deleteTournaments(indexes);
}

function deleteTournamentsCancelled()
{
    tournamentListView.unSelectAll();
}

function updatePlayersView()
{
    playersListView.clear();
    var byteArray = playersContext.players();
    var j = JSON.parse(byteArray);
    for(var i=0;i < j.length;i++)
    {
        var obj = j[i];
        var playerName = obj["playerName"];
        var email = obj["playerMail"];
        playersListView.addItem({"type" : "player","username" : playerName, "mail" : email});
    }
}
function updatePlayerListView()
{
    playersListView.clear();
    applicationInterface.requestPlayers();
}
function updateTournamentListView()
{
    tournamentListView.clear();
    applicationInterface.requestTournaments();
}
function updateTournamentsView()
{
    tournamentListView.clear();
    let byteArray = dartsContext.tournaments();
    var json = JSON.parse(byteArray);
    for(var i = 0;i < json.length;++i)
    {
        let jsonTournament = json[i];
        let gameMode = jsonTournament["gameMode"];
        let title = jsonTournament["title"];
        let winnerName = jsonTournament["winnerName"];
        let playerDetails = jsonTournament["assignedPlayerDetails"];
        let playersCount = playerDetails.length;
        let item = createTournamentItem(gameMode,title,winnerName,playersCount);
        tournamentListView.addItem(item);
    }
}
function createTournamentItem(gameMode, title,winner,playersCount)
{
    return {
        "type" : "tournament",
        "gameMode" : translateGameModeFromHex(gameMode),
        "tournamentTitle" : title,
        "winner" : winner,
        "playersCount" : playersCount
    };
}
function translateGameModeFromHex(gameMode)
{
    if(gameMode === TournamentContext.darts)
        return "First to post"
}
