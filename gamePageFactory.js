function buildTurnController(mode) {
    if(mode === TournamentContext.firstToPost)
        var turnController = Qt.createComponent("TurnController.qml");
    if(turnController === undefined)
        console.log("TurnController: Something went wrong!");
    return turnController;
}

function buildDisplayItem(mode)
{
    var c;
    if(mode === TournamentContext.firstToPost)
    {
        c = Qt.createComponent("KeyDataDisplay.qml");
    }
    if(c === undefined)
        console.log("DisplayItem: Something went wrong!");
    return c;
}

function buildFtpScoreBoard(tableHint)
{
    var c;
    if(tableHint === DataModelContext.singleAttempt)
        c = Qt.createComponent("FtpSingleScoreBoard.qml");
    else
        c = Qt.createComponent("FtpMultiScoreBoard.qml");
    if(c === undefined)
        console.log("ScoreBoard: Something went wrong!");
    return c;
}

function buildAndConnectKeyPad(mode)
{
    var c;
    if(mode === TournamentContext.pointMode)
    {
        c = Qt.createComponent("PointKeyPad.qml");
        connectPointKeyPadInterface(c);
    }

    else if(mode === TournamentContext.scoreMode)
        c = Qt.createComponent("ScoreKeyPad.qml");
    if(c === undefined)
        console.log("PointKeyPad: Something went wrong!");
    return c;
}

function connectPointKeyPadInterface(keyPad)
{
    keyPad.sendInput.connect(FirstToPostScripts.handleKeyPadInput);
}
function connectScoreKeyPadInterface(keyPad)
{
    keyPad.sendInput.connect(FirstToPostScripts.handleKeyPadInput);
}

