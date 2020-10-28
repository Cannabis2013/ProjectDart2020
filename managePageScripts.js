/*
  Begin request tournaments after last player transmitted
  */
function lastPlayerDetailsTransmitted(){
    requestTournaments();
}

/*
  Request removal of tournaments
  */
function deleteTournamentsAccepted()
{
    var indexes = tournamentListView.currentIndexes();
    applicationInterface.handleDeleteTournamentsRequest(indexes);
}
/*
  Handle confirmation of successfull deletion of tournaments
  */
function handleDeleteTournamentsSuccess(status)
{
    if(status)
    {
        tournamentListView.clear();
        requestTournaments();
    }
}

/*
  Delete players accepted
  */

function deletePlayersAccepted(){
    var indexes = playersListView.currentIndexes();
    applicationInterface.handleDeletePlayersRequest(indexes);
}

/*
  Handle confirm deletion of players
  */

function recievePlayersDeletedStatusFromBackend(status)
{
    if(status)
    {
        playersListView.clear();
        tournamentListView.clear();
        requestPlayers();
    }
}

function addPlayer(playerName,email)
{
    playersListView.addItemModel({"type" : "player","username" : playerName, "mail" : email})
}

function recieveTournament(title,numberOfThrows,gameMode,keyPoint,playersCount){
    tournamentListView.addItemModel({"type" : "tournament",
                                        "tournamentTitle" : title,
                                        "Throws" : numberOfThrows,
                                        "KeyPoint" : keyPoint,
                                        "playersCount" : playersCount})
}

function reConnectPlayerInterface()
{
    body.visible = true;
    applicationInterface.transmitResponse.connect(replyFromBackendRecieved); // Handle reply
    playersListView.clear();
    requestPlayers();
}
function reConnectTournamentInterface()
{
    body.visible = true;
    applicationInterface.transmitResponse.connect(replyFromBackendRecieved); // Handle reply
    requestTournaments();
}
