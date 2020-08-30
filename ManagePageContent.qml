import QtQuick 2.0
import QtQuick.Layouts 1.3

import "componentFactory.js" as ComponentFactory

Content {
    id: body

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
    onReplyFromBackendRecieved: {

    }
    GridLayout{
        id: mainLayout
        anchors.fill: parent
        flow: GridLayout.TopToBottom

        ListComponent {
            id: playersListView
            onRequestUpdate: {
                playersListView.clear();
                requestPlayers();
                body.visible = true;
            }
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            height: 256
            componentTitle: "Players"
            labelBackgroundColor: "lightgray"
            itemBackgroundColor: "lightblue"
            itemTitleTextColor: "black"
            itemDescriptionFontColor: "black"
            itemSelectedBackgroundColor: "lightblue"
            titleBackground: "steelblue"
            color: "white"
            radius: 15
            itemTitleFontSize: 16
            itemWidth: playersListView.width*0.95
            itemHeight: 50
            allowCheckState: true
            allowMultipleSelections: true
            instantSelectEnabled: true
            itemDecorator: "qrc:/pictures/Ressources/skull.png"
            imageBackgroundColor: "lightblue"
        }

        GridLayout{
            id: playerCRUDButtons
            flow: GridLayout.LeftToRight

            Rectangle{
                Layout.fillWidth: true
            }
            CRUDButton{
                text: "Create"
                onClicked: {
                    body.visible = false;
                    var createdComponent = ComponentFactory.createPopUp(applicationWindow,
                                                                        "createPlayerPopUp",
                                                                        "CreatePlayerPopUp.qml",
                                                                        0,0,
                                                                        applicationWindow.width,
                                                                        applicationWindow.height);
                    createdComponent.backButtonPressed.connect(playersListView.requestUpdate);
                    applicationInterface.transmitResponse.disconnect(replyFromBackendRecieved);
                }

            }
            CRUDButton{
                text: "Delete"

                onClicked: {
                    var obj = ComponentFactory.createConfirmPopUp('ConfirmPageContent.qml',
                                                                  applicationWindow);
                    obj.acceptClicked.connect(body.deletePlayersAccepted);
                }
            }
        }

        ListComponent {
            id: tournamentListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            onRequestUpdate: {
                tournamentListView.clear();
                requestTournaments();
            }
            color: "white"
            radius: 15
            componentTitle: "Tournaments"
            itemTitleTextColor: "black"
            itemDescriptionFontColor: "black"
            itemSelectedBackgroundColor: "lightblue"
            itemSelectedtextColor: "black"
            itemHoveredColor: "lightblue"
            itemBackgroundColor: "lightblue"
            itemTitleFontSize: 20
            itemDescriptionFontSize: 12
            titleBackground: "steelblue"
            itemWidth: tournamentListView.width *0.95
            itemHeight: 64
            allowCheckState: true
            allowMultipleSelections: true
            instantSelectEnabled: true
            itemDecorator: "qrc:/pictures/Ressources/darttournamentmod.png"
        }
        GridLayout{
            id: tournamentCRUDButtons
            flow: GridLayout.LeftToRight

            Rectangle{
                Layout.fillWidth: true
            }
            CRUDButton{
                text: "Create"
            }
            CRUDButton{
                text: "Delete"
                onClicked: {
                    var obj = ComponentFactory.createConfirmPopUp('ConfirmPageContent.qml',
                                                                  applicationWindow);
                    obj.acceptClicked.connect(body.deleteTournamentsAccepted);
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
