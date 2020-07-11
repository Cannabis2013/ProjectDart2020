function initializeScoreBoard(){
    var currentTournament = localDart.currentActiveTournamentID();
    if(currentTournament === "")
    {
        print("No currently active tournament");
        return;
    }
    var tournamentLegsCount = localDart.tournamentLegsCount(currentTournament);
    var playersCount = localDart.tournamentPlayersCount(currentTournament);
    // Append headers
    for(var i = 0;i < playersCount;i++){
        var playerID = localDart.assignedPlayerIDfromIndex(currentTournament,i);
        var fullName = localDart.playerFirstName(playerID) + " " + localDart.playerLastName(playerID);
        scoreTable.appendHeader(fullName);
    }
    var headerItemsCount = scoreTable.getHeaderItemCount(0x2);
    scoreTable.initialValue = localDart.tournamentKeyPoint(currentTournament);
    for(var j = 0;j < headerItemsCount;j++){
        var headerItem = scoreTable.getHeaderItem(j,0x2);
        var player = localDart.playerIDFromFullName(headerItem);
        var roundIndex = 1;
        var legIndex = 0;
        var initialScore = localDart.tournamentKeyPoint(currentTournament);
        var subtractedScore = initialScore;
        while(1)
        {
            var point = localDart.pointValue(currentTournament,player,roundIndex,legIndex++);
            if(point < 0)
                break;
            subtractedScore -= point;
            scoreTable.appendData(headerItem,subtractedScore);
            if(legIndex % tournamentLegsCount == 0)
            {
                roundIndex++;
                legIndex = 0;
            }
        }
    }
    updateNavigator();
}
function initializeFromGameStatus()
{
    var status = localDart.gameStatus();
    if(turnNavigator.startButtonText == "Restart")
    {
        var tournament = localDart.currentActiveTournamentID();
        localDart.resetTournament(tournament);
        localDart.startGame();
        turnNavigator.startButtonText = "Pause";
        keyPad.enableKeys = true;
    }

    if(status === 0xc) // 0xc = idle
    {
        localDart.startGame();
        turnNavigator.startButtonText = "Pause";
        keyPad.enableKeys = true;
    }
    else if(status === 0xe) // 0xe = running
    {

        localDart.stopGame();
        turnNavigator.startButtonText = "Resume";
        keyPad.enableKeys = false;
    }
    else if(status === 0x10) // 0x10 = Winner declared
    {
        turnNavigator.startButtonText = "Restart";
        keyPad.enableKeys = false;
    }
    updateNavigator();
}

function checkGameStatus()
{
    var status = localDart.gameStatus();
    if(status === 0x10) // 0x10 = Winner declated
    {
        turnNavigator.startButtonText = "Restart";
        keyPad.enableKeys = false;
    }
}

function updateNavigator()
{
    var currentRoundIndex = localDart.currentGameRoundIndex();
    var currentPlayer = localDart.currentActivePlayer();

    turnNavigator.currentRoundIndex = currentRoundIndex;
    turnNavigator.currentPlayer = currentPlayer;
}

function handleInput(val)
{
    var playerName = localDart.currentActivePlayer();
    var status = localDart.addPoint(val);
    var score = localDart.score(playerName);
    scoreTable.appendData(playerName,score);
    turnNavigator.refreshTurnKeys();
    updateNavigator();
    checkGameStatus();
}

function handleUndo()
{
    if(localDart.undoTurn() === 0x11) // 0x11 = operation successfull
    {
        updateNavigator();
        turnNavigator.refreshTurnKeys();
        var fullName = localDart.currentActivePlayer();
        scoreTable.takeData(fullName);
    }
}
