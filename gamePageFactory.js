function buildTurnController(mode,scoreBoardMode) {
    if(mode === TournamentContext.firstToPost)
    {
        var c = Qt.createComponent("FirstToPostTurnController.qml");
    }
    if(c === undefined)
        console.log("Something went wrong!");
    return c;
}

function buildDisplayItem(mode,scoreBoardMode)
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

function buildScoreBoard(mode,scoreBoardMode)
{
    if(mode === TournamentContext.firstToPost)
    {
        if(scoreBoardMode === TournamentContext.singleDimensional)
            var c = Qt.createComponent("FTPSingleScoreBoard.qml");
    }
    if(c === undefined)
        console.log("Something went wrong!");
    return c;
}

function buildKeyPad(mode,scoreBoardMode)
{
    if(mode === 0x1)
    {
        var c = Qt.createComponent("DefaultKeyPadComponent.qml");
    }
    if(c === undefined)
        console.log("Something went wrong!");
    return c;
}

