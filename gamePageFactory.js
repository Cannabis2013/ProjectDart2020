function buildTurnController(mode) {
    if(mode === TournamentContext.firstToPost)
    {
        var turnController = Qt.createComponent("FirstToPostTurnController.qml");
    }
    if(turnController === undefined)
        console.log("Something went wrong!");
    return turnController;
}

function buildDisplayItem(mode)
{
    var c;
    if(mode === TournamentContext.firstToPost)
    {
        c = Qt.createComponent("DisplayKeyDataItem.qml");
    }
    if(c === undefined)
        console.log("Something went wrong!");
    return c;
}

function buildFTPScoreBoard(tableHint)
{
    var c;
    if(tableHint === DataModelContext.singleAttempt)
        c = Qt.createComponent("FTPSingleScoreBoard.qml");
    else
        c = Qt.createComponent("FTPMultiScoreBoard.qml");
    if(c === undefined)
        console.log("Something went wrong!");
    return c;
}

function buildKeyPad(mode)
{
    var c;
    if(mode === TournamentContext.pointMode)
        c = Qt.createComponent("PointKeyPad.qml");
    else if(mode === TournamentContext.scoreMode)
        c = Qt.createComponent("ScoreKeyPad.qml");
    if(c === undefined)
        console.log("Something went wrong!");
    return c;
}

