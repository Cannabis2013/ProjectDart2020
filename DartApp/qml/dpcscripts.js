.import "dpccontrollerinterface.js" as DPCInterface
.import "dpcinit.js" as DPInit
.import "dpcupdatecomponents.js" as UpdateComponents

function startGame()
{
    if(DPCInterface.getStatus() !== 0)
        return;
    UpdateComponents.updateTurnValues();
    dpcContent.state = "waitingForInput";
}

function handleScoreKeyPadInput(value, modKeyCode){
    dpcContent.state = "waitingForInputConfirmation";
    let response = DPCInterface.addInput(value);
    UpdateComponents.updateScoreBoard(response);
    UpdateComponents.updateTurnValues();
    setState("waitingForInput");
}

function undoClicked()
{
    dpcContent.state = "waitingForInputConfirmation";
    let response = DPCInterface.undoTurn();
    UpdateComponents.updateScoreBoard(response);
    UpdateComponents.updateTurnValues();
    setState("waitingForInput");
}

function redoClicked()
{
    dpcContent.state = "waitingForInputConfirmation";
    let response = DPCInterface.redoTurn();
    UpdateComponents.updateScoreBoard(response);
    UpdateComponents.updateTurnValues();
    setState("waitingForInput");
}

function setState(state)
{
    let status = DPCInterface.getStatus();
    if(status === 0)
        dpcContent.state = state;
    else if(status === 2)
        UpdateComponents.setWinnerDetails();
}

function resetTournament()
{
    dpcContent.state = "stopped";
    if(DPCInterface.reset())
    {
        UpdateComponents.clearComponents();
        DPInit.init();
    }
}
