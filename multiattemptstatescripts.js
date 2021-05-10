function declareWinner()
{
    multiPointTurnController.backendHasDeclaredAWinner();
    pointKeyPad.enableKeyPad(false);
    GameGeneralScripts.setWinnerText();
}

function backendIsStopped()
{
    multiPointTurnController.backendIsStopped();
    pointKeyPad.enableKeyPad(false);
}

function backendProcessesInput()
{
    multiPointTurnController.backendProcessesInput();
    pointKeyPad.enableKeyPad(false);
}

function backendAwaitsInput()
{
    multiPointTurnController.backendAwaitsInput();
    pointKeyPad.enableKeyPad(true);
}
