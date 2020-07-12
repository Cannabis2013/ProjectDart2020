function updateInterface(){
    var tournamentsCount = localDart.tournamentsCount();

    for(var i = 0; i < tournamentsCount;i++)
    {
        var id = localDart.tournamentIDFromIndex(i);
        var title = localDart.tournamentTitle(id);
        var legsCount = localDart.tournamentLegsCount(id);
        var maxPlayersCount = localDart.tournamentMaxPlayers(id);
        var keyPoint = localDart.tournamentKeyPoint(id);
        var playersCount = localDart.tournamentPlayersCount(id);

        tournamentListView.addTournamentItem(title,maxPlayersCount,legsCount,keyPoint,playersCount);
    }
}

function startGame(){
    var currentlySelectedIndex = tournamentListView.currentlySelectedIndex;
    var tournamentID = localDart.tournamentIDFromIndex(currentlySelectedIndex);
    if(tournamentID === "")
        return;
    var tournamentPlayersCount = localDart.tournamentPlayersCount(tournamentID);
    if(tournamentPlayersCount === 0)
        return;
    var result = localDart.setCurrentActiveTournament(tournamentID);
    if(result === "")
        return;
    startGameClicked();
}
