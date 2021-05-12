function declareWinner()
{
    multiAttemptScoreTurnController.backendHasDeclaredAWinner();
    scoreKeyPad.enableKeyPad(false);
    MultiAttemptScripts.setWinnerText();
}

function backendIsStopped()
{
    multiAttemptScoreTurnController.backendIsStopped();
    scoreKeyPad.enableKeyPad(false);
}

function backendProcessesInput()
{
    multiAttemptScoreTurnController.backendProcessesInput();
    scoreKeyPad.enableKeyPad(false);
}

function backendAwaitsInput()
{
    multiAttemptScoreTurnController.backendAwaitsInput();
    scoreKeyPad.enableKeyPad(true);
}
