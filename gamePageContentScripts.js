function initializeScoreBoard(){
    var currentTournamentID = localDart.currentActiveTournamentID();
    if(currentTournamentID === "")
    {
        print("No currently active tournament");
        return;
    }

    var tournamentLegsCount = localDart.tournamentLegsCount(currentTournamentID);
    var playersCount = localDart.tournamentPlayersCount(currentTournamentID);
    // Append headers
    for(var i = 0;i < playersCount;i++){
        var playerID = localDart.assignedPlayerIDfromIndex(currentTournamentID,i);
        var fullName = localDart.playerFirstName(playerID) + " " + localDart.playerLastName(playerID);
        scoreTable.appendHeader(fullName);
    }
    var headerItemsCount = scoreTable.getHeaderItemCount(0x2);
    scoreTable.initialValue = localDart.tournamentKeyPoint(currentTournamentID);
    for(var j = 0;j < headerItemsCount;j++){
        var headerItem = scoreTable.getHeaderItem(j,0x2);
        var player = localDart.playerIDFromFullName(headerItem);
        var roundIndex = 1;
        var legIndex = 0;
        var initialScore = localDart.tournamentKeyPoint(currentTournamentID);
        var subtractedScore = initialScore;
        while(1)
        {
            var point = localDart.pointValue(currentTournamentID,player,roundIndex,legIndex++);
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

}

function handleInput(val)
{
    var playerName = localDart.currentActivePlayer();
    var status = localDart.addPoint(val);
    var score = localDart.score(playerName);
    scoreTable.appendData(playerName,score);
}
