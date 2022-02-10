function init()
{
    updatePlayersView();
    updateTournamentsView();
}
function requestDeletePlayerPopUp()
{
    let selectedIndexes = playersListView.selectedIndexes();
    let count = selectedIndexes.length;
    if(count > 0)
        PopupBuilder.createConfirmPopUp(applicationWindow,delPlayCancel,delPlayAccept);
}
function delPlayCancel()
{
    playersListView.unSelectAll();
}
function delPlayAccept(){
    var indexes = playersListView.selectedIndexes();
    playersContext.remove(indexes);
    updatePlayersView();
}
function requestDeleteTournamentPopUp()
{
    let selectedIndexes = tournamentListView.selectedIndexes();
    let count = selectedIndexes.length;
    if(count > 0)
        PopupBuilder.createConfirmPopUp(applicationWindow,deleteTournamentsCancelled,deleteTournamentsAccepted);
}
function deleteTournamentsAccepted()
{
    let indexes = tournamentListView.selectedIndexes();
    dartsContext.deleteTournaments(indexes);
    updateTournamentsView();
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
        playersListView.addItem(jsonToItem(obj));
    }
}
function jsonToItem(obj)
{
    var item = {
        "type" : "player",
        "username" : obj["name"],
        "mail" : obj["mail"]
    }
    return item;
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
        let playerDetails = jsonTournament["players"];
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
