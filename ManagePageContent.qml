import QtQuick 2.0
import QtQuick.Layouts 1.3

import "componentFactory.js" as ComponentFactory

Content {
    id: body

    signal requestCreatePlayerPage
    signal requestCreateTournamentPage
    signal requestPlayers
    signal requestDeletePlayers(var indexes)
    signal requestTournaments
    signal requestDeleteTournaments(var indexes)

    /*
      Begin request tournaments after last player transmitted
      */
    function lastPlayerDetailsTransmitted(){
        requestTournaments();
    }

    /*
      Request removal of tournaments
      */
    function requestDeleteTournamentPopUp()
    {
        let selectedIndexes = tournamentListView.currentIndexes();
        let count = selectedIndexes.length;
        if(count > 0)
        {
            let obj = ComponentFactory.createConfirmPopUp('ConfirmPageContent.qml',
                                                          applicationWindow);
            obj.acceptClicked.connect(body.deleteTournamentsAccepted);
        }
    }

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
    GridLayout{
        id: mainLayout
        anchors.fill: parent
        flow: GridLayout.TopToBottom

        DefaultPlayerListView {
            id: playersListView
            componentTitle: "Players"
            labelTextColor: ThemeContext.manPlayerListViewLabelColor
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            onRequestUpdate: {
                playersListView.clear();
                requestPlayers();
            }
        }

        GridLayout{
            id: playerCRUDButtons
            flow: GridLayout.LeftToRight

            Rectangle{
                Layout.fillWidth: true
            }
            CRUDButton{
                text: "Create"
                onClicked: requestCreatePlayerPage()
            }
            CRUDButton{
                text: "Delete"
                onClicked: requestDeletePlayerPopUp()
            }
        }
        DefaultTournamentListView {
            id: tournamentListView
            Layout.fillHeight: true
            Layout.fillWidth: true

            labelTextColor: ThemeContext.manTournamentListViewLabelColor

            onRequestUpdate: {
                tournamentListView.clear();
                requestTournaments();
            }
        }
        GridLayout{
            id: tournamentCRUDButtons
            flow: GridLayout.LeftToRight

            Rectangle{
                Layout.fillWidth: true
            }
            CRUDButton{
                text: "Create"
                onClicked: requestCreateTournamentPage()
            }
            CRUDButton{
                text: "Delete"
                onClicked: {
                    requestDeleteTournamentPopUp();
                }
            }
        }
    }
    Component.onCompleted: {
        body.requestDeletePlayers.connect(applicationInterface.handleDeletePlayersRequest);
        body.requestPlayers.connect(applicationInterface.requestPlayers); // Request initial/continous players
        applicationInterface.sendPlayerDetail.connect(body.addPlayer); // Recieve initial players
        body.requestTournaments.connect(applicationInterface.handleTournamentsRequest); // Request initial tournaments
        applicationInterface.sendRequestedTournament.connect(recieveTournament);
        applicationInterface.playersDeletedStatus.connect(body.recievePlayersDeletedStatusFromBackend);
        applicationInterface.tournamentsDeletedSuccess.connect(body.handleDeleteTournamentsSuccess);
        applicationInterface.lastPlayerDetailsTransmitted.connect(body.lastPlayerDetailsTransmitted);
        requestPlayers();
    }
    Component.onDestruction: {
        body.requestPlayers.disconnect(applicationInterface.requestPlayers); // Request initial/continous players
        applicationInterface.sendPlayerDetail.disconnect(body.addPlayer); // Recieve initial players
        body.requestTournaments.disconnect(applicationInterface.handleTournamentsRequest); // Request initial tournaments
        applicationInterface.sendRequestedTournament.disconnect(recieveTournament);
        applicationInterface.playersDeletedStatus.disconnect(body.recievePlayersDeletedStatusFromBackend);
        applicationInterface.tournamentsDeletedSuccess.disconnect(body.handleDeleteTournamentsSuccess);
        applicationInterface.lastPlayerDetailsTransmitted.disconnect(body.lastPlayerDetailsTransmitted);
    }
}
