import QtQuick 2.0
import QtQuick.Layouts 1.3

Content {
    id: body

    signal requestPlayers
    signal requestDelePlayers(var indexes)
    signal requestTournaments
    signal requestDeleteTournaments(var indexes)

    function addPlayer(userName,email)
    {
        playersListView.addItemModel({"type" : "player","username" : userName, "mail" : email})
    }

    function recieveTournament(title,numberOfThrows,gameMode,keyPoint,playersCount){
        tournamentListView.addItemModel({"type" : "tournament",
                                            "tournamentTitle" : title,
                                            "Throws" : numberOfThrows,
                                            "KeyPoint" : keyPoint,
                                            "playersCount" : playersCount})
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
            Layout.fillHeight: true
            componentTitle: "Assign players"
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
            itemDecorator: "qrc:/pictures/Ressources/darttournamentmod.png"
        }

        GridLayout{
            id: playerCRUDButtons
            flow: GridLayout.LeftToRight

            Rectangle{
                Layout.fillWidth: true
            }
            CRUDButton{
                text: "Create"
            }
            CRUDButton{
                text: "Delete"
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
            onItemClicked: sendClickedTournamentIndex(index)
            itemTitleFontSize: 20
            itemDescriptionFontSize: 12
            itemWidth: tournamentListView.width *0.95
            itemHeight: 64
            allowCheckState: true
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
            }
        }
    }
    Component.onCompleted: {
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
