function getTournamentValues()
{
    let id = dpController.tournamentId();
    var tournamentAsByteArray = dartsContext.tournament(id);
    let tournamentAsJson = JSON.parse(tournamentAsByteArray);
    return tournamentAsJson;
}
function getPlayerInputs(tournamentJson)
{
    let id = tournamentJson["tournamentId"];
    let byteArray = dartsContext.inputs(id);
    let json = JSON.parse(byteArray);
    let inputs = [];
    for(var i = 0;i < json.length;i++)
    {
        let player = json[i];
        let input = {
            name : player["inputPlayerName"],
            score : player["score"],
            modCode : player["modKeyCode"]
        };
        inputs.push(input);
    }
    return inputs;
}
function getPlayerNames(tournamentJson)
{
    let playerDetails = tournamentJson["assignedPlayerDetails"];
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
function getPlayerScores()
{
    let byteArray = dpController.getPlayerScores();
    let json = JSON.parse(byteArray);
    let list = [];
    for(var i = 0;i < json.length;++i)
    {
        let playerScore = json[i];
        let obj = {
            name : playerScore["inputPlayerName"],
            remScore : playerScore["remainingScore"]
        }
        list.push(obj);
    }
    return list;
}
function getStatus()
{
    return dpController.status();
}
function getTurnValues()
{
    var byteArray = dpController.getTurnValues();
    var json = JSON.parse(byteArray);
    return json;
}
function getWinnerValues()
{
    var byteArray = dpController.getWinnerJson();
    var json = JSON.parse(byteArray);
    var winnerDetails = json["WinnerDetails"];
    return winnerDetails;
}
function addInput(point, modKeyCode)
{
    var obj = {point : point, modKeyCode : modKeyCode};
    var json = JSON.stringify(obj);
    var response = dpController.addInput(json);
    return JSON.parse(response);
}
function undoTurn()
{
    var response = dpController.undoTurn();
    return JSON.parse(response);
}
function redoTurn()
{
    var response = dpController.redoTurn();
    return JSON.parse(response);
}
function reset()
{
    return dpController.reset()
}
