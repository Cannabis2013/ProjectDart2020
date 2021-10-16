function initialize()
{
    connect();
    applicationInterface.requestTournaments();
}

function connect()
{
    applicationInterface.sendTournaments.connect(recieveTournaments);
    applicationInterface.dartsPointMultiColumnsInitialized.connect(dartsPointMultiColumnInitialized);
    applicationInterface.dartsScoreSingleColumnInitialized.connect(dartsScoreSingleColumnInitialized);
    applicationInterface.dartsPointSingleColumnInitialized.connect(dartsPointSingleColumnInitialized);
}

function disconnect()
{
    applicationInterface.sendTournaments.disconnect(recieveTournaments);
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
        var assignedPlayerDetails = jsonTournament["assignedPlayerDetails"];
        var assignedPlayersCount = assignedPlayerDetails.length;
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
