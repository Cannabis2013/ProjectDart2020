.import "dsccontrollercontext.js" as DSCInterface

function init()
{
    let tnmValues = createControllerValues();
    initStatistics(tnmValues);
    initHeader(tnmValues);
    initScoreBoard(tnmValues);
    let status = DSCInterface.getStatus();
    if(status === 0)
        dscContent.state = "ready";
    else if(status === 2)
        winnerFound();
}

function createControllerValues()
{
    let tournamentJson = DSCInterface.getTournamentValues();
    let playerNames = DSCInterface.getPlayerNames(tournamentJson);
    var playerScores = DSCInterface.getPlayerScores();
    let playerInputs = DSCInterface.getPlayerInputs(tournamentJson);
    let values = {
        title : tournamentJson["title"],
        winnerName : tournamentJson["winnerName"],
        initRemScore : tournamentJson["initRemScore"],
        playerNames : playerNames,
        playerInputs : playerInputs,
        playerScores : playerScores
    };
    return values;
}

function initStatistics(tnmValues)
{
    let names = tnmValues.playerNames;
    for(var i = 0;i < names.length;i++)
    {
        let name = names[i];
        statistics.addPlayer(name);
    }
    let inputs = tnmValues.playerInputs;
    for(var j = 0;j < inputs.length;j++)
    {
        let input = inputs[j];
        statistics.addSnapShot(input.name,input.score,input.modKeyCode);
    }
}

function initHeader(metaVals)
{
    let playerNames = metaVals.playerNames;
    let initRemScore = metaVals.initRemScore;
    singleColumnScoreBoard.appendHeaderData(playerNames,initRemScore);
}

function initScoreBoard(tnmVals)
{
    let playerScores = tnmVals.playerScores;
    for(var i = 0;i < playerScores.length;++i)
    {
        let obj = playerScores[i];
        let playerName = obj.name;
        let playerScore = obj.remScore;
        let reportAsByteArray = statistics.createReport(playerName);
        let report = JSON.parse(reportAsByteArray);
        let minVal = report["minimum"];
        let midVal = report["middle"];
        let maxVal = report["maximum"];
        singleColumnScoreBoard.setData(playerName,playerScore,minVal,midVal,maxVal);
    }
}

function winnerFound()
{
    var json = DSCInterface.getWinnerValues();
    keyDataDisplay.setCurrentWinner(json["winnerName"]);
    keyDataDisplay.setThrowSuggestion("");
    dscContent.state = "winner";
}
