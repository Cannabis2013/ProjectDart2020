
function buildFtpScoreBoard(displayHint, inputHint, attempts)
{
    if(displayHint === DataModelContext.singleAttempt)
    {
        // Build singledimensional scoreboard
        let c = Qt.createComponent("FtpSingleScoreBoard.qml");
        applicationInterface.ftpControllerAddedAndPersistedScore.connect(FirstToPostScripts.extractScoreFromJson);
        return c;
    }
    else if(displayHint === DataModelContext.multiAttempt)
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
        applicationInterface.ftpControllerAddedAndPersistedScore.connect(FirstToPostScripts.extractPointScoreFromJson);
        c.attempts = attempts;
        return c;
    }
    else if(inputHint === TournamentContext.scoreMode)
    {
        let c = Qt.createComponent("FtpMultiScoreScoreBoard.qml");
        return c;
    }
}
