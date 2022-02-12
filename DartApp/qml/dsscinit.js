function init()
{
    let tnmValues = getValuesFromController();
    initStatistics(tnmValues);
    initHeader(tnmValues);
    initScoreBoard(tnmValues);
    let status = dsController.status();
    if(status === 0)
        dsscContent.state = "ready";
    else if(status === 2)
        winnerFound();
}
function getValuesFromController()
{
    let id = dsController.tournamentId();
    let metaJson = JSON.parse(dartsContext.tournament(id));
    let playerDetails = metaJson["players"];
    let playerNames = getPlayerNames(playerDetails);
    var playerScores = getPlayerScores();
    let playerInputs = getPlayerInputs(id);
    let values = {
        title : metaJson["title"],
        winnerName : metaJson["winnerName"],
        initRemScore : metaJson["initRemScore"],
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
        statistics.addSnapShots(input);
    }
}
function getPlayerInputs(id)
{
    let byteArray = dartsContext.inputs(id);
    let json = JSON.parse(byteArray);
    let inputs = [];
    for(var i = 0;json.length;i++)
    {
        let input = {
            name : json["inputPlayerName"],
            score : json["score"],
            modCode = json["modKeyCode"]
        };
        inputs.push(input);
    }
    return inputs;
}
function getPlayerNames(playerDetails)
{
    let playerNames = [];
    let count = playerDetails.length;
    for(var i = 0;i < count;i++)
    {
        let playerDetail = playerDetails[i];
        let playerName = playerDetail["playerName"];
        playerNames.push(playerName);
    }
    return playerNames;
}
function initHeader(metaVals)
{
    let playerNames = metaVals.playerNames;
    let initRemScore = metaVals.initRemScore;
    singleColumnScoreBoard.appendHeaderData(playerNames,initRemScore);
}

function getPlayerScores()
{
    let byteArray = dsController.getPlayerScores();
    let json = JSON.parse(byteArray);
    let list = [];
    for(var i = 0;i < json.length;++i)
    {
        let obj = {
            name : json["inputPlayerName"],
            remScore : json["remainingScore"]
        }
        list.push(obj);
    }
    return list;
}
function initScoreBoard(tnmVals)
{
    let playerScores = tnmVals.playerScores;
    for(var i = 0;i < playerScores;++i)
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
    var byteArray = dsController.getWinnerJson();
    var json = JSON.parse(byteArray);
    keyDataDisplay.setCurrentWinner(json["winnerName"]);
    keyDataDisplay.setThrowSuggestion("");
    dsscContent.state = "winner";
}

function resetTournament()
{
    dsscContent.state = "stopped";
    var result = dsController.reset();
    if(result)
    {
        clearComponents();
        init();
    }
}
function clearComponents()
{
    singleColumnScoreBoard.clearData();
    singleColumnScoreTurnController.reset();
    keyDataDisplay.clear();
}

