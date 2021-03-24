function createPopUp(parentID, id,fileName,x, y, width, height)
{
    var component = Qt.createComponent(fileName);
    var properties = {
        "id" : id,
        "x" : x,
        "y" : y,
        "width" : width,
        "height" : height,
        "anchors.fill" : parentID
     };
    var createPlayerPopUp = component.createObject(parentID, properties);
    if(createPlayerPopUp === null)
        print("Something went very wrong. Call the police if necessary.");
    return createPlayerPopUp;
}

function createConfirmPopUp(fileName, parentID)
{
    var component = Qt.createComponent(fileName);
    var properties = {
        "x" : 0,
        "y" : 0,
        "width" : parentID.width,
        "height" : parentID.height,
        "anchors.fill" : parentID,
        "isPopUp" : true
     };
    var instantiatedObject = component.createObject(parentID, properties);
    if(instantiatedObject === null)
        print("Something went very wrong. Call the police if necessary.");
    return instantiatedObject;
}


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
        var obj = createConfirmPopUp('ConfirmPageContent.qml',
                                                      applicationWindow);
        obj.acceptClicked.connect(deletePlayersAccepted);
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
        let obj = createConfirmPopUp('ConfirmPageContent.qml',
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
  Add player to listview
  */
function recievePlayers(players)
{
    for(var i=0;i < players.length;i += 2)
    {
        var playerName = players[i];
        var email = players[i+1];
        playersListView.addItemModel({"type" : "player","username" : playerName, "mail" : email})
    }
    requestTournaments();
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

// Recieve tournament data
function recieveTournaments(tournaments)
{
    for(var i = 0;i < tournaments.length;i += 5)
    {
        var title = tournaments[i + 1];
        var gameMode = tournaments[i+2];
        var winnerName = tournaments[i+3];
        var playersCount = tournaments[i + 4];
        tournamentListView.addItemModel(
                    {
                        "type" : "tournament",
                        "gameMode" : translateGameModeFromHex(gameMode),
                        "tournamentTitle" : title,
                        "winner" : winnerName,
                        "playersCount" : playersCount
                    });
    }
}


function translateGameModeFromHex(gameMode)
{
    if(gameMode === TournamentContext.firstToPost)
        return "First to post"
}

/*
  Connect/disconnect interface
  */
function connectInterface(){
    body.requestDeletePlayers.connect(applicationInterface.handleDeletePlayersRequest);
    body.requestPlayers.connect(applicationInterface.requestPlayerDetails); // Request initial/continous players
    applicationInterface.sendPlayers.connect(recievePlayers); // Recieve initial players
    body.requestTournaments.connect(applicationInterface.handleTournamentsRequest); // Request initial tournaments
    applicationInterface.sendTournaments.connect(recieveTournaments);
    applicationInterface.playersDeletedStatus.connect(recievePlayersDeletedStatusFromBackend);
    applicationInterface.tournamentsDeletedSuccess.connect(handleDeleteTournamentsSuccess);
}
function disconnectInterface(){
    body.requestPlayers.disconnect(applicationInterface.requestPlayerDetails); // Request initial/continous players
    applicationInterface.sendPlayers.disconnect(recievePlayers); // Recieve initial players
    body.requestTournaments.disconnect(applicationInterface.handleTournamentsRequest); // Request initial tournaments
    applicationInterface.sendTournaments.disconnect(recieveTournaments);
    applicationInterface.playersDeletedStatus.disconnect(recievePlayersDeletedStatusFromBackend);
    applicationInterface.tournamentsDeletedSuccess.disconnect(handleDeleteTournamentsSuccess);

}
