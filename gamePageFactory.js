function buildTurnController(mode) {
    if(mode === TournamentContext.darts)
        var turnController = Qt.createComponent("TurnController.qml");
    if(turnController === undefined)
        console.log("TurnController: Something went wrong!");
    return turnController;
}

function buildDisplayItem(mode)
{
    var c;
    if(mode === TournamentContext.darts)
    {
        c = Qt.createComponent("KeyDataDisplay.qml");
    }
    if(c === undefined)
        console.log("DisplayItem: Something went wrong!");
    return c;
}
function buildFtpScoreBoard(displayHint,inputHint,attempts)
{
    let c = FtpScoreBoardFactory.buildFtpScoreBoard(displayHint,
                                                    inputHint,
                                                    attempts);
    if(c === undefined)
        throw "Undefined";
    return c;
}

function buildAndConnectKeyPad(mode)
{
    var c;
    if(mode === TournamentContext.pointMode)
    {
        c = Qt.createComponent("PointKeyPad.qml");
        if(c === undefined)
            console.log("PointKeyPad: Something went wrong!");
    }

    else if(mode === TournamentContext.scoreMode)
    {
        c = Qt.createComponent("ScoreKeyPad.qml");
        if(c === undefined)
            console.log("ScoreKeyPad: Something went wrong!");
    }
    return c;
}

