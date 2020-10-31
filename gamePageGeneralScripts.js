/*
  Connect signals and slots
  */
function connectComponents()
{
    body.requestMetaInformation.connect(applicationInterface.handleTournamentMetaRequest);
    applicationInterface.sendTournamentMetaData.connect(body.handleMetaInformation);
    body.requestScoreBoardData.connect(applicationInterface.handleScoreBoardRequest);
    applicationInterface.sendPlayerScore.connect(appendScore);
    body.requestStart.connect(applicationInterface.handleRequestStart);
    body.requestStop.connect(applicationInterface.handleRequestStop);
    body.requestRestart.connect(applicationInterface.handleRestartTournament);
    body.sendInput.connect(applicationInterface.handleUserInput);
    body.requestUndo.connect(applicationInterface.handleUndoRequest);
    body.requestRedo.connect(applicationInterface.handleRedoRequest);
    body.requestStatusFromBackend.connect(applicationInterface.handleControllerStateRequest);
}
function disconnectComponents()
{
    body.requestMetaInformation.disconnect(applicationInterface.handleTournamentMetaRequest);
    applicationInterface.sendTournamentMetaData.disconnect(body.handleMetaInformation);
    body.requestScoreBoardData.disconnect(applicationInterface.handleScoreBoardRequest);
    applicationInterface.sendPlayerScore.disconnect(appendScore);
    body.requestStart.disconnect(applicationInterface.handleRequestStart);
    body.requestStop.disconnect(applicationInterface.handleRequestStop);
    body.requestRestart.disconnect(applicationInterface.handleRestartTournament);
    body.sendInput.disconnect(applicationInterface.handleUserInput);
    body.requestUndo.disconnect(applicationInterface.requestUndo);
    body.requestRedo.disconnect(applicationInterface.requestRedo);
    body.requestStatusFromBackend.disconnect(applicationInterface.handleControllerStateRequest);
}

/*
  Handle ScoreData related stuff
  */
function appendScore(player,point,score, keyCode)
{
    body.scoreRecieved(player,point,score,keyCode);
}
function takeScore(player)
{
    if(currentTournamentMetaData.tournamentGameMode === 0x1)
        scoreBoardItemSlot.item.takeData(player);
}

/*
  Handle reply from backend
  */
function handleReplyFromBackend(response,args)
{
    var buttonText = turnControllerItemSlot.item.startButtonText, playerName, scoreValue;
    if(response === 0x3A) // Gamecontroller is stopped
    {
        if(body.state !== "preRestart")
            body.state = "stopped";
    }
    else if(response === 0x2D) // Gamecontroller is ready and awaits input
    {
        let canUndo = args[0];
        let canRedo = args[1];
        let currentRoundIndex = args[2];
        let currentPlayerUserName = args[3];
        let throwSuggestion = args[4];

        let suggestion = textSourceContainer.throwSuggestLabel + " " + throwSuggestion;
        notificationItemSlot.item.setThrowSuggestion(suggestion);
        turnControllerItemSlot.item.updateState(currentRoundIndex,
                                                currentPlayerUserName,
                                                canUndo,
                                                canRedo);
        body.state = "waitingForInput";
    }
    else if(response === 0x10) // Backend replies end of transmission
    {
        handleRecievedScores(args);
        body.requestStatusFromBackend();
    }

    else if(response === 0x45) // Backend is initialized and ready
    {
        body.state = "ready";
    }
    else if(response === 0x29) // Backend is reset
    {
        setupFirstToPostScoreTable();
        body.state = "ready"
    }
    /*
      Backend responds that it has updated its datacontext
      */
    else if(response === 0x27) // Controller is in AddScoreState
    {
        playerName = args[0];
        let pointValue = args[1];
        scoreValue = args[2];
        let keyCode = args[3];
        appendScore(playerName,pointValue,scoreValue,keyCode);
        requestStatusFromBackend();
    }

    else if(response === 0x28) // Controller is in UndoState
    {
        playerName = args[0];
        takeScore(playerName);
        requestStatusFromBackend();
    }
    else if(response === 0x15) // Winner declared
    {
        currentTournamentMetaData.determinedWinner = args[0];
        body.state = "winner";

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
        body.scoreRecieved(name,point,score,keyCode);
    }
}
/*
  Handle user input
  */
function handleKeyPadInput(value,keyCode){
    body.state = "waitingForInputConfirmation";
    body.sendInput(value,keyCode);
}
/*
  Handle TurnController events
  */
function handleStartPressAndHold()
{
    if(body.state === "waitingForInput")
        body.state = "preRestart";
    else if(body.state === "ready")
        body.state = "preRestart";
    else if(body.state === "winner")
        body.state = "preRestart";
    else if(body.state === "preRestart")
        body.state = "ready";
}
function handleStartClicked()
{
    var buttonText = turnControllerItemSlot.item.startButtonText;
    if(buttonText === buttonTextContainer.startText ||
            buttonText === buttonTextContainer.resumeText)
        requestStart();
    else if(buttonText === buttonTextContainer.restartText)
        body.state = "restart";
    else
    {
        body.state = "pauseState";
        requestStop();
    }
}
/*
  Handle Notification related stuff
  */
function handleSetWinnerText(text)
{
    notificationItemSlot.item.setCurrentWinner(text);
}
