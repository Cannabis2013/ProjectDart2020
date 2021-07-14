function initialize()
{
    connect();
    body.requestTournaments();
}

function connect()
{
    body.requestTournaments.connect(applicationInterface.handleTournamentsRequest); // Request initial tournaments
    applicationInterface.sendTournaments.connect(recieveTournaments);
    body.sendClickedTournamentIndex.connect(applicationInterface.handleSetCurrentTournamentRequest);
    applicationInterface.dartsPointMultiColumnsInitialized.connect(dartsPointMultiColumnInitialized);
    applicationInterface.dartsScoreSingleColumnInitialized.connect(dartsScoreSingleColumnInitialized);
    applicationInterface.dartsPointSingleColumnInitialized.connect(dartsPointSingleColumnInitialized);
}

function disconnect()
{
    body.requestTournaments.disconnect(applicationInterface.handleTournamentsRequest);
    applicationInterface.sendTournaments.disconnect(recieveTournaments);
    body.sendClickedTournamentIndex.disconnect(applicationInterface.handleSetCurrentTournamentRequest);
    applicationInterface.dartsPointMultiColumnsInitialized.disconnect(dartsPointMultiColumnInitialized);
    applicationInterface.dartsScoreSingleColumnInitialized.disconnect(dartsScoreSingleColumnInitialized);
    applicationInterface.dartsPointSingleColumnInitialized.disconnect(dartsPointSingleColumnInitialized);
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
        var assignedPlayerNames = jsonTournament["assignedPlayerNames"];
        var assignedPlayersCount = assignedPlayerNames.length;
        tournamentListView.addItem(
                    {
                        "type" : "tournament",
                        "gameMode" : translateGameModeFromHex(gameMode),
                        "tournamentTitle" : title,
                        "winner" : winnerName,
                        "playersCount" : assignedPlayersCount
                    });
    }
}

function translateGameModeFromHex(gameMode)
{
    if(gameMode === TournamentContext.darts)
        return "First to post"
}
