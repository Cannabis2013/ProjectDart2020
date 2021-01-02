/*
  Delete player
    - Request delete player popup
    - Handle delete player accept
    - Handle delete player reply from backend
  */
function requestDeletePlayerPopUp()
{
    let selectedIndex = playersListView.currentIndexes();
    let count = selectedIndex.length;
    if(count > 0)
    {
        var obj = ComponentFactory.createConfirmPopUp('ConfirmPageContent.qml',
                                                      applicationWindow);
        obj.acceptClicked.connect(body.deletePlayersAccepted);
    }
}
function deletePlayersAccepted(){
    var indexes = playersListView.currentIndexes();
    applicationInterface.handleDeletePlayersRequest(indexes);
}
function recievePlayersDeletedStatusFromBackend(status)
{
    if(status)
    {
        playersListView.clear();
        tournamentListView.clear();
        requestPlayers();
    }
}
/*
  Request removal of tournaments
    - Handle request delete tournament popup
    - Handle delete tournament accept
    - Handle delete tournament reply from backend
  */
function requestDeleteTournamentPopUp()
{
    let selectedIndexes = tournamentListView.currentIndexes();
    let count = selectedIndexes.length;
    if(count > 0)
    {
        let obj = ComponentFactory.createConfirmPopUp('ConfirmPageContent.qml',
                                                      applicationWindow);
        obj.acceptClicked.connect(deleteTournamentsAccepted);
    }
}
function deleteTournamentsAccepted()
{
    var indexes = tournamentListView.currentIndexes();
    applicationInterface.handleDeleteTournamentsRequest(indexes);
}
function handleDeleteTournamentsSuccess(status)
{
    if(status)
    {
        tournamentListView.clear();
        requestTournaments();
    }
}
/*
  Begin request tournaments after last player transmitted
  */
function lastPlayerDetailsTransmitted(){
    requestTournaments();
}
/*
  Add player to listview
  */
function addPlayer(playerName,email)
{
    playersListView.addItemModel({"type" : "player","username" : playerName, "mail" : email})
}
/*
  Update player listview
  */
function updatePlayerListView()
{
    playersListView.clear();
    requestPlayers();
}
/*
  Update tournament listview
  */
function updateTournamentListView()
{
    tournamentListView.clear();
    requestTournaments();
}

/*
  Connect/disconnect interface
  */
function connectInterface(){
    body.requestDeletePlayers.connect(applicationInterface.handleDeletePlayersRequest);
    body.requestPlayers.connect(applicationInterface.requestPlayers); // Request initial/continous players
    applicationInterface.sendPlayerDetail.connect(addPlayer); // Recieve initial players
    body.requestTournaments.connect(applicationInterface.handleTournamentsRequest); // Request initial tournaments
    applicationInterface.sendRequestedTournament.connect(body.recieveTournament);
    applicationInterface.playersDeletedStatus.connect(recievePlayersDeletedStatusFromBackend);
    applicationInterface.tournamentsDeletedSuccess.connect(handleDeleteTournamentsSuccess);
    applicationInterface.lastPlayerDetailsTransmitted.connect(lastPlayerDetailsTransmitted);
}
function disconnectInterface(){
    body.requestPlayers.disconnect(applicationInterface.requestPlayers); // Request initial/continous players
    applicationInterface.sendPlayerDetail.disconnect(addPlayer); // Recieve initial players
    body.requestTournaments.disconnect(applicationInterface.handleTournamentsRequest); // Request initial tournaments
    applicationInterface.sendRequestedTournament.disconnect(body.recieveTournament);
    applicationInterface.playersDeletedStatus.disconnect(recievePlayersDeletedStatusFromBackend);
    applicationInterface.tournamentsDeletedSuccess.disconnect(handleDeleteTournamentsSuccess);
    applicationInterface.lastPlayerDetailsTransmitted.disconnect(lastPlayerDetailsTransmitted);
}
