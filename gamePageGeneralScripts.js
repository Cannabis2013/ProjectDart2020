/*
  Connect signals and slots
  */
function connectComponents()
{
    gamePageBody.requestMetaInformation.connect(applicationInterface.handleTournamentMetaRequest);
    applicationInterface.sendFTPTournamentMetaData.connect(handleFTPTournamentMetaData);
    gamePageBody.requestScoreBoardData.connect(applicationInterface.handleScoreBoardRequest);
    applicationInterface.sendPlayerScore.connect(appendScore);
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
    gamePageBody.requestMetaInformation.disconnect(applicationInterface.handleTournamentMetaRequest);
    applicationInterface.sendFTPTournamentMetaData.disconnect(handleFTPTournamentMetaData);
    gamePageBody.requestScoreBoardData.disconnect(applicationInterface.handleScoreBoardRequest);
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
  Handle initializing
  */
function handleFTPTournamentMetaData(stringArray, numericArray, playerNames){
    tournamentMetaData.tournamentTitle = stringArray[0];
    tournamentMetaData.determinedWinner = stringArray[1];
    tournamentMetaData.tournamentGameMode = numericArray[0];
    tournamentMetaData.tournamentKeyPoint = numericArray[1];
    tournamentMetaData.tournamentTableViewHint = numericArray[2];
    tournamentMetaData.tournamentInputMode = numericArray[3];
    tournamentMetaData.assignedPlayers = playerNames;
    if(tournamentMetaData.tournamentGameMode === 0x1)
        FirstToPostScripts.setupFirstToPost();
}
/*
  Handle ScoreData related stuff
  */
function appendScore(player,point,score, keyCode)
{
    gamePageBody.scoreRecieved(player,point,score,keyCode);
}
function takeScore(player,score,point)
{
    if(tournamentMetaData.tournamentGameMode === 0x1)
        scoreBoardInterface().takeData(player,point,score);
}

/*
  Handle reply from backend
  */
function handleReplyFromBackend(response,args)
{
    if(response === 0x3A) // Gamecontroller is stopped
    {
        if(gamePageBody.state !== "preRestart")
            gamePageBody.state = "stopped";
    }
    else if(response === 0x2D) // Gamecontroller is ready and awaits input
    {
        let canUndo = args[0];
        let canRedo = args[1];
        let currentRoundIndex = args[2];
        let currentPlayerUserName = args[3];
        let throwSuggestion = args[4];

        let suggestion = textSourceContainer.throwSuggestLabel + " " + throwSuggestion;
        gamePageBody.notificationInterface().setThrowSuggestion(suggestion);
        gamePageBody.turnControllerInterface().updateState(currentRoundIndex,
                                                currentPlayerUserName,
                                                canUndo,
                                                canRedo);
        gamePageBody.state = "waitingForInput";
    }
    else if(response === 0x10) // Backend replies end of transmission
    {
        handleRecievedScores(args);
        gamePageBody.requestStatusFromBackend();
    }

    else if(response === 0x45) // Backend is initialized and ready
    {
        gamePageBody.state = "ready";
    }
    else if(response === 0x29) // Backend is reset
    {
        let keyPoint = args[0];
        let names = args[1];

        for(var i = 0;i < names.length;i++)
        {
            let name = names[i];
            appendScore(name,0,keyPoint,-1);
        }
        requestStatusFromBackend();
    }
    /*
      Backend responds that it has updated its datacontext
      */
    else if(response === 0x27) // Controller transmit scores/points
    {
        let playerName = args[0];
        let pointValue = args[1];
        let scoreValue = args[2];
        let keyCode = args[3];
        appendScore(playerName,pointValue,scoreValue,keyCode);
        requestStatusFromBackend();
    }

    else if(response === 0x28) // Controller is in UndoState
    {
        let playerName = args[0];
        let scoreValue = args[1];
        let pointValue = args[2];
        takeScore(playerName,scoreValue,pointValue);
        requestStatusFromBackend();
    }
    else if(response === 0x15) // Winner declared
    {
        tournamentMetaData.determinedWinner = args[0];
        gamePageBody.state = "winner";

    }
    else if(response === 0x17) // Backend is initialized
    {
        turnControllerItemSlot.item.startButtonEnabled = true;
    }
}
/*
  Handle recieved score
  */
function handleRecievedScores(data)
{
    if(data.length % 4 !== 0)
        return;
    for(var i = 0; i < data.length;i += 4)
    {
        var name = data[i];
        var point = data[i +1];
        var score = data[i + 2];
        var keyCode = data[i + 3];
        gamePageBody.scoreRecieved(name,point,score,keyCode);
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
