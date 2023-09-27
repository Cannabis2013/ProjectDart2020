.import "dpccontrollerinterface.js" as DPCInterface

function init()
{
    let tnmValues = createControllerValues();
    initStatistics(tnmValues);
    initHeader(tnmValues);
    initScoreBoard(tnmValues);
    let status = DPCInterface.getStatus();
    if(status === 0)
        dpcContent.state = "ready";
    else if(status === 2)
        winnerFound();
}

function createControllerValues()
{
    let tournamentJson = DPCInterface.getTournamentValues();
    let playerNames = DPCInterface.getPlayerNames(tournamentJson);
    var playerScores = DPCInterface.getPlayerScores();
    let playerInputs = DPCInterface.getPlayerInputs(tournamentJson);
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
    dpcScoreBoard.appendHeaderData(playerNames,initRemScore);
}

function initScoreBoard(tnmVals)
{
    let playerScores = tnmVals.playerScores;
    for(var i = 0;i < playerScores.length;++i)
    {
        let obj = playerScores[i];
        let playerName = obj.name;
        let playerScore = obj.remScore;
        let inGame = obj.inGame;
        let reportAsByteArray = statistics.createReport(playerName);
        let report = JSON.parse(reportAsByteArray);
        let minVal = report["minimum"];
        let midVal = report["middle"];
        let maxVal = report["maximum"];
        dpcScoreBoard.setData(playerName,playerScore,minVal,midVal,maxVal, inGame);
    }
}

function winnerFound()
{
    var json = DPCInterface.getWinnerValues();
    keyDataDisplay.setCurrentWinner(json["winnerName"]);
    keyDataDisplay.setThrowSuggestion("");
    dpcContent.state = "winner";
}
