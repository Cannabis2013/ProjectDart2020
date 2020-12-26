function buildTurnController(mode,scoreBoardMode) {
    if(mode === 0x1)
    {
        var c = Qt.createComponent("FirstToPostTurnController.qml");
    }
    return c;
}

function buildDisplayItem(mode,scoreBoardMode)
{
    if(mode === TournamentContext.singleDimensional)
    {
        var c = Qt.createComponent("DisplayKeyDataItem.qml");
    }
    return c;
}

function buildScoreBoard(mode,scoreBoardMode)
{
    if(mode === 0x1)
    {
        if(scoreBoardMode === TournamentContext.singleDimensional)
            var c = Qt.createComponent("FTPSingleScoreBoard.qml");
    }

    return c;
}

function buildKeyPad(mode,scoreBoardMode)
{
    if(mode === 0x1)
    {
        var c = Qt.createComponent("DefaultKeyPadComponent.qml");
    }
    return c;
}

