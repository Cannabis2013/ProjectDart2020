.import "dsccontrollerinterface.js" as DSCInterface
.import "dscinit.js" as DSInit
.import "updatedsccontext.js" as UpdateDSC

function startGame()
{
    if(DSCInterface.getStatus() === 0)
    {
        UpdateDSC.updateTurnValues();
        dscContent.state = "waitingForInput";
    }
}

function handleScoreKeyPadInput(value){
    dscContent.state = "waitingForInputConfirmation";
    var response = UpdateDSC.addInput(value);
    UpdateDSC.updateScoreBoard(response);
    UpdateDSC.updateTurnValues();
    setState("waitingForInput");
}

function undoClicked()
{
    dscContent.state = "waitingForInputConfirmation";
    var response = DSCInterface.undoTurn();
    UpdateDSC.updateScoreBoard(response);
    UpdateDSC.updateTurnValues();
    setState("waitingForInput");
}

function redoClicked()
{
    dscContent.state = "waitingForInputConfirmation";
    var response = DSCInterface.redoTurn();
    UpdateDSC.updateScoreBoard(response);
    UpdateDSC.updateTurnValues();
    setState("waitingForInput");
}

function setState(state)
{
    let status = DSCInterface.getStatus();
    if(status === 0)
        dscContent.state = state;
    else if(status === 2)
        UpdateDSC.setWinnerDetails();
}

function resetTournament()
{
    dscContent.state = "stopped";
    if(DSCInterface.reset())
    {
        UpdateDSC.clearComponents();
        DSInit.init();
    }
}
