function declareWinner()
{
    singleColumnScoreTurnController.backendHasDeclaredAWinner();
    scoreKeyPad.enableKeyPad(false);
    DartsScoresScripts.setWinnerText();
}

function backendIsStopped()
{
    singleColumnScoreTurnController.backendIsStopped();
    scoreKeyPad.enableKeyPad(false);
}

function backendProcessesInput()
{
    singleColumnScoreTurnController.backendProcessesInput();
    scoreKeyPad.enableKeyPad(false);
}

function backendAwaitsInput()
{
    singleColumnScoreTurnController.backendAwaitsInput();
    scoreKeyPad.enableKeyPad(true);
}
