function initialize()
{
    var byteArray = dartsContext.tournaments();
    var jsonTournaments= JSON.parse(byteArray);
    var jsonLength = jsonTournaments.length;
    for(var i = 0;i < jsonLength;++i)
    {
        var jsonTournament = jsonTournaments[i];
        var gameMode = jsonTournament["gameMode"];
        var title = jsonTournament["title"];
        var winnerName = jsonTournament["winnerName"];
        var players = jsonTournament["assignedPlayerDetails"];
        var playersCount = players.length;
        dartsListView.addItem(createItem(title,gameMode,winnerName,playersCount));
    }
}

function createItem(title, gameMode, winnerName, playersCount)
{
    var item = {
        "type" : "tournament",
        "gameMode" : toGameMode(gameMode),
        "tournamentTitle" : title,
        "winner" : winnerName,
        "playersCount" : playersCount
    };
    return item;
}

function toGameMode(gameMode)
{
    if(gameMode === TournamentContext.darts)
        return "First to post"
}

function initializeDarts(index)
{
    var byteArray = dartsContext.tournament(index);
    var json = JSON.parse(byteArray);
    var hint = json["inputHint"];
    if(hint === TournamentContext.pointMode)
        initializeDartsPointController(json);
    else if(hint === TournamentContext.scoreMode)
        initializeDartsScoreController(json);
    else
        throw "Bad inputhint!";

}
function initializeDartsPointController(json)
{
    var status = dpController.initialize(json["tournamentId"],json["keyPoint"]);
    if(status === 0)
        body.dartsPointSingleColumnInitialized();
    else
        throw "Bad init!";
}

function initializeDartsScoreController(json)
{
    var status = dsController.initialize(json["tournamentId"],json["keyPoint"]);
    if(status === 0)
        body.dartsScoreSingleColumnInitialized();
    else
        throw "Bad init!";
}
