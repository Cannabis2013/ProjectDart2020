function init()
{
    var jsonTournaments= JSON.parse(dartsContext.tournaments());
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

function processSelection(index)
{
    let json = JSON.parse(dartsContext.tournament(index));
    let tournamentId = json["tournamentId"];
    let isConsistent = dartsContext.isConsistent(tournamentId);
    let result = true;
    if(!isConsistent) result = tryRepairTournament(tournamentId,index);
    if(result) initDarts(json);
}

function tryRepairTournament(tournamentId,index)
{
    dartsListView.removeItems([index]);
    return dartsContext.tryRepair(tournamentId);
}

function initDarts(json)
{
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
    let status = dpController.initialize(json["tournamentId"]);
    if(status === 0)
        body.dartsPointSingleColumnInitialized();
    else
        throw "Bad init!";
}

function initializeDartsScoreController(json)
{
    let status = dsController.initialize(json["tournamentId"]);
    if(status === 0)
        body.dartsScoreSingleColumnInitialized();
    else
        throw "Bad init!";
}
