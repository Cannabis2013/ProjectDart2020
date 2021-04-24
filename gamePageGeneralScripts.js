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
    applicationInterface.controllerHasDeclaredAWinner.connect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.controllerIsInitialized.connect(backendIsInitialized);
    gamePageBody.requestMetaInformation.connect(applicationInterface.handleTournamentMetaRequest);
    applicationInterface.sendFTPTournamentMetaData.connect(handleFTPTournamentMetaData);
    gamePageBody.requestStart.connect(applicationInterface.handleRequestStart);
    gamePageBody.requestStop.connect(applicationInterface.handleRequestStop);
    gamePageBody.requestRestart.connect(applicationInterface.handleRestartTournament);
    gamePageBody.sendInput.connect(applicationInterface.handleUserInput);
    gamePageBody.requestUndo.connect(applicationInterface.handleUndoRequest);
    gamePageBody.requestRedo.connect(applicationInterface.handleRedoRequest);
    gamePageBody.requestStatusFromBackend.connect(applicationInterface.handleControllerStateRequest);
}
function disconnectComponents()
{
    applicationInterface.controllerHasDeclaredAWinner.disconnect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.disconnect(backendIsStopped);
    applicationInterface.controllerIsInitialized.disconnect(backendIsInitialized);
    gamePageBody.requestMetaInformation.disconnect(applicationInterface.handleTournamentMetaRequest);
    applicationInterface.sendFTPTournamentMetaData.disconnect(handleFTPTournamentMetaData);
    gamePageBody.requestStart.disconnect(applicationInterface.handleRequestStart);
    gamePageBody.requestStop.disconnect(applicationInterface.handleRequestStop);
    gamePageBody.requestRestart.disconnect(applicationInterface.handleRestartTournament);
    gamePageBody.sendInput.disconnect(applicationInterface.handleUserInput);
    gamePageBody.requestUndo.disconnect(applicationInterface.requestUndo);
    gamePageBody.requestRedo.disconnect(applicationInterface.requestRedo);
    gamePageBody.requestStatusFromBackend.disconnect(applicationInterface.handleControllerStateRequest);
}

function handleFTPTournamentMetaData(data){
    var json = JSON.parse(data);

    var ftpComponent = Qt.createComponent("FirstToPostMetaData.qml");
    var properties = {
        "tournamentTitle" : json["title"],
        "determinedWinner" : json["winnerName"],
        "tournamentGameMode" : json["gameMode"],
        "tournamentKeyPoint" : json["keyPoint"],
        "attempts" : json["attempts"],
        "tournamentTableViewHint" : json["displayHint"],
        "tournamentInputMode" : json["inputHint"],
        "assignedPlayers" : json["assignedPlayerNames"]
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
  Handle Notification related stuff
  */
function setWinnerText()
{
    var winnerName = textSourceContainer.winnerLabel + " " +
            tournamentMetaData.determinedWinner;
    notificationItemSlot.item.setCurrentWinner(winnerName);
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

function backendDeclaredAWinner(data)
{
    var json = JSON.parse(data);
    tournamentMetaData.determinedWinner = json.winner;
    gamePageBody.state = "winner";
}
