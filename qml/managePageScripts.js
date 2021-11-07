function connectInterface(){
    applicationInterface.sendPlayers.connect(recievePlayers);
    applicationInterface.sendTournaments.connect(recieveTournaments);
    applicationInterface.playersDeletedStatus.connect(recievePlayersDeletedStatusFromBackend);
    applicationInterface.tournamentsDeletedSuccess.connect(handleDeleteTournamentsSuccess);
}
function disconnectInterface(){
    applicationInterface.sendPlayers.disconnect(recievePlayers);
    applicationInterface.sendTournaments.disconnect(recieveTournaments);
    applicationInterface.playersDeletedStatus.disconnect(recievePlayersDeletedStatusFromBackend);
    applicationInterface.tournamentsDeletedSuccess.disconnect(handleDeleteTournamentsSuccess);
}

function requestDeletePlayerPopUp()
{
    let selectedIndex = playersListView.currentIndexes;
    let count = selectedIndex.length;
    playersListView.unSelectAll();
    if(count > 0)
        PopupBuilder.createConfirmPopUp(applicationWindow,deletePlayersAccepted);
}
function deletePlayersAccepted(){
    var indexes = playersListView.currentIndexes;
    applicationInterface.requestDeletePlayers(indexes);
}

function recievePlayersDeletedStatusFromBackend(status)
{
    if(status)
    {
        playersListView.clear();
        tournamentListView.clear();
        applicationInterface.requestPlayers();
    }
}

function requestDeleteTournamentPopUp()
{
    let selectedIndexes = tournamentListView.currentIndexes;
    let count = selectedIndexes.length;
    tournamentListView.unSelectAll();
    if(count > 0)
        PopupBuilder.createConfirmPopUp(applicationWindow,deleteTournamentsAccepted);
}

function deleteTournamentsAccepted()
{
    var indexes = tournamentListView.currentIndexes;
    applicationInterface.requestDeleteTournaments(indexes);
}

function handleDeleteTournamentsSuccess(status)
{
    if(status)
    {
        tournamentListView.clear();
        applicationInterface.requestTournaments();
    }
}

function recievePlayers(data)
{
    var j = JSON.parse(data);
    for(var i=0;i < j.length;i++)
    {
        var obj = j[i];
        var playerName = obj["playerName"];
        var email = obj["playerMail"];
        playersListView.addItem({"type" : "player","username" : playerName, "mail" : email});
    }
    applicationInterface.requestTournaments();
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

function recieveTournaments(json)
{
    var jsonTournaments= JSON.parse(json);
    var jsonLength = jsonTournaments.length;
    for(var i = 0;i < jsonLength;++i)
    {
        var jsonTournament = jsonTournaments[i];
        var gameMode = jsonTournament["gameMode"];
        var title = jsonTournament["title"];
        var winnerName = jsonTournament["winnerName"];
        var assignedPlayerDetails = jsonTournament["assignedPlayerDetails"];
        var assignedPlayersCount = assignedPlayerDetails.length;
        var item = createTournamentItem(gameMode,title,winnerName,assignedPlayersCount);
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
