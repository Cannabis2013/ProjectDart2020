import QtQuick 2.0
import QtQuick.Layouts 1.3

import "componentFactory.js" as ComponentFactory

Content {
    id: body

    signal requestPlayers
    signal requestDeletePlayers(var indexes)
    signal requestTournaments
    signal requestDeleteTournaments(var indexes)

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
        if(response == 0x26 || response == 0x45)
        {
            playersListView.clear();
            requestPlayers();
        }
        else if(response == ox24 || response == 0x44)
        {
            tournamentListView.clear();
            requestTournaments();
        }
    }
    GridLayout{
        id: mainLayout
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        /*
          TODO: Fix a player listview with appropriate CRUD buttons
          TODO: Fix a tournament listview with appropriate CRUD buttons
          */

        ListComponent {
            id: playersListView
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            height: 256
            componentTitle: "Assign players"
            labelBackgroundColor: "lightgray"
            itemBackgroundColor: "lightblue"
            itemTextColor: "black"
            itemHoveredColor: "lightblue"
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
                    var createdComponent = ComponentFactory.createPopUp(applicationWindow,"createPlayerPopUp",0,0,applicationWindow.width,applicationWindow.height);
                    createdComponent.backButtonPressed.connect(body.reConnectPlayerInterface);
                    applicationInterface.transmitResponse.disconnect(replyFromBackendRecieved);
                }

            }
            CRUDButton{
                text: "Delete"

                onClicked: {
                    var indexes = playersListView.currentIndexes();
                    requestDeletePlayers(indexes);
                }
            }
        }

        ListComponent {
            id: tournamentListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "white"
            radius: 15
            componentTitle: "Select tournament"
            itemTextColor: "black"
            itemSelectedBackgroundColor: "silver"
            itemSelectedtextColor: "black"
            itemHoveredColor: "darkgray"
            itemBackgroundColor: "lightblue"
            itemTitleFontSize: 20
            itemDescriptionFontSize: 12
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
                onClicked: requestDeleteTournaments(tournamentListView.currentIndexes())
            }
        }
    }
    Component.onCompleted: {
        body.requestDeletePlayers.connect(applicationInterface.handleDeletePlayersRequest);
        body.requestPlayers.connect(applicationInterface.requestPlayers); // Request initial/continous players
        applicationInterface.sendPlayerDetail.connect(body.addPlayer); // Recieve initial players
        body.requestTournaments.connect(applicationInterface.handleTournamentsRequest); // Request initial tournaments
        applicationInterface.sendRequestedTournament.connect(recieveTournament);

        requestPlayers();
        requestTournaments();
    }
    Component.onDestruction: {
        body.requestPlayers.disconnect(applicationInterface.requestPlayers); // Request initial/continous players
        applicationInterface.sendPlayerDetail.disconnect(body.addPlayer); // Recieve initial players
        body.requestTournaments.disconnect(applicationInterface.handleTournamentsRequest); // Request initial tournaments
        applicationInterface.sendRequestedTournament.connect(recieveTournament);
    }
}
