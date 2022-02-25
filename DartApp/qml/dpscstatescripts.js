function declareWinner()
{
    dpcTurnController.backendHasDeclaredAWinner();
    pointKeyPad.enableKeyPad(false);
}

function backendIsStopped()
{
    dpcTurnController.backendIsStopped();
    pointKeyPad.enableKeyPad(false);
}

function backendProcessesInput()
{
    dpcTurnController.backendProcessesInput();
    pointKeyPad.enableKeyPad(false);
}

function backendAwaitsInput()
{
    dpcTurnController.backendAwaitsInput();
    pointKeyPad.enableKeyPad(true);
}
