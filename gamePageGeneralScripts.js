// Handle construction/destruction
function initializeComponent()
{
    connectComponents();
    gamePageBody.requestMetaInformation();
}

/*
  Connect signals and slots
  */
function connectComponents()
{
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.controllerIsInitialized.connect(backendIsInitialized);
    gamePageBody.requestMetaInformation.connect(applicationInterface.handleTournamentMetaRequest);
    applicationInterface.sendFTPTournamentMetaData.connect(handleFTPTournamentMetaData);
    applicationInterface.sendPlayerScore.connect(appendScore);
    gamePageBody.requestStart.connect(applicationInterface.handleRequestStart);
    gamePageBody.requestStop.connect(applicationInterface.handleRequestStop);
    gamePageBody.requestRestart.connect(applicationInterface.handleRestartTournament);
    gamePageBody.sendInput.connect(applicationInterface.handleUserInput);
    gamePageBody.requestUndo.connect(applicationInterface.handleUndoRequest);
    gamePageBody.requestRedo.connect(applicationInterface.handleRedoRequest);
    gamePageBody.requestStatusFromBackend.connect(applicationInterface.handleControllerStateRequest);
    gamePageBody.requestPersistState.connect(applicationInterface.handlePersistTournamentRequest);
}
function disconnectComponents()
{
    applicationInterface.controllerIsStopped.disconnect(backendIsStopped);
    applicationInterface.controllerIsInitialized.disconnect(backendIsInitialized);
    gamePageBody.requestMetaInformation.disconnect(applicationInterface.handleTournamentMetaRequest);
    applicationInterface.sendFTPTournamentMetaData.disconnect(handleFTPTournamentMetaData);
    applicationInterface.sendPlayerScore.disconnect(appendScore);
    gamePageBody.requestStart.disconnect(applicationInterface.handleRequestStart);
    gamePageBody.requestStop.disconnect(applicationInterface.handleRequestStop);
    gamePageBody.requestRestart.disconnect(applicationInterface.handleRestartTournament);
    gamePageBody.sendInput.disconnect(applicationInterface.handleUserInput);
    gamePageBody.requestUndo.disconnect(applicationInterface.requestUndo);
    gamePageBody.requestRedo.disconnect(applicationInterface.requestRedo);
    gamePageBody.requestStatusFromBackend.disconnect(applicationInterface.handleControllerStateRequest);
}
/*
  Handle recieved 'First to Post tournament' meta data

  Passed data structure:
   - String values are placed in a list of strings
   | in the following locations:
       [0] = Tournament title
       [1] = Tournament winner name
   - Numeric values are placed in a list of integers
   | in the following locations:
       [0] = Tournamaent game mode
       [1] = Tournament keypoint
       [2] = Tournament model tablehint
       [3] = Tournament input mode {Accumulated input for all sets, Input for every set}
  */
function handleFTPTournamentMetaData(stringArray, numericArray, playerNames){
    var ftpComponent = Qt.createComponent("FirstToPostMetaData.qml");
    var properties = {
        "tournamentTitle" : stringArray[0],
        "determinedWinner" : stringArray[1],
        "tournamentGameMode" : numericArray[0],
        "tournamentKeyPoint" : numericArray[1],
        "attempts" : numericArray[2],
        "tournamentTableViewHint" : numericArray[3],
        "tournamentInputMode" : numericArray[4],
        "assignedPlayers" : playerNames
    }
    var metaDataObject = ftpComponent.createObject(gamePageBody,properties);
    gamePageBody.tournamentMetaData = metaDataObject;
    FirstToPostScripts.buildFtpComponents();
}
/*
  Handle ScoreData related stuff
  */
function appendScore(player,point,score, keyCode)
{
    gamePageBody.scoreRecieved(player,point,score,keyCode);
}

/*
  Handle reply from backend
  */
function handleReplyFromBackend(response,args)
{
    if(response === 0x15) // Winner declared
    {
        tournamentMetaData.determinedWinner = args[0];
        gamePageBody.state = "winner";

    }
    else if(response === 0x3B)
    {
        requestQuit();
    }
}

/*
  Handle user input
  */
function handleKeyPadInput(value,keyCode){
    gamePageBody.state = "waitingForInputConfirmation";
    gamePageBody.sendInput(value,keyCode);
}
/*
  Handle Notification related stuff
  */
function handleSetWinnerText(text)
{
    notificationItemSlot.item.setCurrentWinner(text);
}

function handleRequestTournamentReset()
{
    if(gamePageBody.state === "ready")
        gamePageBody.state = "stopped";
}
// Backend states
function backendIsStopped()
{
    if(gamePageBody.state !== "preRestart")
        gamePageBody.state = "stopped";
}

function backendIsInitialized()
{
    gamePageBody.state = "ready";
}
