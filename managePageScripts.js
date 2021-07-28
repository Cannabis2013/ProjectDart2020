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
        printNullObjectErrorMessage();
    return createPlayerPopUp;
}

function printNullObjectErrorMessage()
{
    print("Something went very wrong. Call the police if necessary.");
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
        printNullObjectErrorMessage();
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
    applicationInterface.requestDeletePlayers(indexes);
}

function recievePlayersDeletedStatusFromBackend(status)
{
    if(status)
    {
        playersListView.clear();
        tournamentListView.clear();
        applicationInterface.requestPlayers();
    }
}

function requestDeleteTournamentPopUp()
{
    let selectedIndexes = tournamentListView.currentIndexes;
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
    var indexes = tournamentListView.currentIndexes;
    applicationInterface.requestDeleteTournaments(indexes);
}

function handleDeleteTournamentsSuccess(status)
{
    if(status)
    {
        tournamentListView.clear();
        applicationInterface.requestTournaments();
    }
}
/*
  Add player to listview
  */
function recievePlayers(data)
{
    var j = JSON.parse(data);
    for(var i=0;i < j.length;i++)
    {
        var obj = j[i];
        var playerName = obj["playerName"];
        var email = obj["playerMail"];
        playersListView.addItemModel({"type" : "player","username" : playerName, "mail" : email});
    }
    applicationInterface.requestTournaments();
}
/*
  Update player listview
  */
function updatePlayerListView()
{
    playersListView.clear();
    applicationInterface.requestPlayers();
}

function updateTournamentListView()
{
    tournamentListView.clear();
    applicationInterface.requestTournaments();
}

function recieveTournaments(json)
{
    var jsonTournaments= JSON.parse(json);
    var jsonLength = jsonTournaments.length;
    for(var i = 0;i < jsonLength;++i)
    {
        var jsonTournament = jsonTournaments[i];
        var gameMode = jsonTournament["gameMode"];
        var title = jsonTournament["title"];
        var winnerName = jsonTournament["winnerName"];
        var assignedPlayerNames = jsonTournament["assignedPlayerNames"];
        var assignedPlayersCount = assignedPlayerNames.length;
        tournamentListView.addItem(
                    {
                        "type" : "tournament",
                        "gameMode" : translateGameModeFromHex(gameMode),
                        "tournamentTitle" : title,
                        "winner" : winnerName,
                        "playersCount" : assignedPlayersCount
                    });
    }
}


function translateGameModeFromHex(gameMode)
{
    if(gameMode === TournamentContext.darts)
        return "First to post"
}

function connectInterface(){
    applicationInterface.sendPlayers.connect(recievePlayers); // Recieve initial players
    applicationInterface.sendTournaments.connect(recieveTournaments);
    applicationInterface.playersDeletedStatus.connect(recievePlayersDeletedStatusFromBackend);
    applicationInterface.tournamentsDeletedSuccess.connect(handleDeleteTournamentsSuccess);
}
function disconnectInterface(){
    applicationInterface.sendPlayers.disconnect(recievePlayers); // Recieve initial players
    applicationInterface.sendTournaments.disconnect(recieveTournaments);
    applicationInterface.playersDeletedStatus.disconnect(recievePlayersDeletedStatusFromBackend);
    applicationInterface.tournamentsDeletedSuccess.disconnect(handleDeleteTournamentsSuccess);
}
