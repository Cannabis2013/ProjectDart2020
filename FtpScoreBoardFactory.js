
function buildFtpScoreBoard(displayHint, inputHint, attempts)
{
    if(displayHint === DataModelContext.SingleAttempt)
    {
        // Build singledimensional scoreboard
        let c = Qt.createComponent("FtpSingleScoreBoard.qml");
        return c;
    }
    else if(displayHint === DataModelContext.MultiAttempt)
    {
        // Build multi dimensional scoreboard
        let c = buildMultiDimensionalScoreBoard(inputHint,attempts);
        return c;
    }
}

function buildMultiDimensionalScoreBoard(inputHint, attempts)
{
    if(inputHint === TournamentContext.pointMode)
    {
        let c = Qt.createComponent("FtpMultiPointScoreBoard.qml");
        c.attempts = attempts;
        return c;
    }
    else if(inputHint === TournamentContext.scoreMode)
    {
        let c = Qt.createComponent("FtpMultiScoreScoreBoard.qml");
        return c;
    }
}
