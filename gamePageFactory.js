function buildTurnController(mode) {
    if(mode === TournamentContext.firstToPost)
    {
        var c = Qt.createComponent("FirstToPostTurnController.qml");
    }
    if(c === undefined)
        console.log("Something went wrong!");
    return c;
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

function buildScoreBoard(mode,scoreBoardMode)
{
    var c;
    if(mode === TournamentContext.firstToPost)
    {
        if(scoreBoardMode === DataModelContext.singleDimensional)
            c = Qt.createComponent("FTPSingleScoreBoard.qml");
        else
            c = Qt.createComponent("FTPMultiScoreBoard.qml");
    }
    if(c === undefined)
        console.log("Something went wrong!");
    return c;
}

function buildKeyPad(mode)
{
    if(mode === 0x1)
    {
        var c = Qt.createComponent("DefaultKeyPadComponent.qml");
    }
    if(c === undefined)
        console.log("Something went wrong!");
    return c;
}
