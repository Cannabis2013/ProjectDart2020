function declareWinner()
{
    pointSingleColumnTurnController.backendHasDeclaredAWinner();
    pointKeyPad.enableKeyPad(false);
}

function backendIsStopped()
{
    pointSingleColumnTurnController.backendIsStopped();
    pointKeyPad.enableKeyPad(false);
}

function backendProcessesInput()
{
    pointSingleColumnTurnController.backendProcessesInput();
    pointKeyPad.enableKeyPad(false);
}

function backendAwaitsInput()
{
    pointSingleColumnTurnController.backendAwaitsInput();
    pointKeyPad.enableKeyPad(true);
}
