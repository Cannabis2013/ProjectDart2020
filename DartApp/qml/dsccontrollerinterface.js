function getTournamentValues()
{
    let id = dsController.tournamentId();
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
    let byteArray = dsController.getPlayerScores();
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

function getStatus() {return dsController.status();}

function getTurnValues()
{
    var byteArray = dsController.getTurnValues();
    var json = JSON.parse(byteArray);
    return json;
}

function getWinnerValues()
{
    var byteArray = dsController.getWinnerJson();
    var json = JSON.parse(byteArray);
    var winnerDetails = json["WinnerDetails"];
    return winnerDetails;
}

function undoTurn()
{
    var response = dsController.undoTurn();
    return JSON.parse(response);
}

function redoTurn()
{
    var response = dsController.redoTurn();
    return JSON.parse(response);
}

function reset() {return dsController.reset();}
