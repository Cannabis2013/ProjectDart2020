import QtQuick 2.12
import QtQuick.Layouts 1.3
import "componentFactory.js" as ComponentFactory
import "managePageScripts.js" as ManageScripts
Content {
    id: body
    signal requestCreatePlayerPage
    signal requestCreateTournamentPage
    signal requestPlayers
    signal requestDeletePlayers(var indexes)
    signal requestTournaments
    signal requestDeleteTournaments(var indexes)
    signal recieveTournament(string title,
                             int numberOfThrows,
                             int gameMode,
                             int keyPoint,
                             int playersCount)
    onRecieveTournament: tournamentListView.addItemModel({"type" : "tournament",
                                                             "tournamentTitle" : title,
                                                             "Throws" : numberOfThrows,
                                                             "KeyPoint" : keyPoint,
                                                             "playersCount" : playersCount})
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
            onRequestUpdate: ManageScripts.updatePlayerListView()
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
                onClicked: ManageScripts.requestDeletePlayerPopUp()
            }
        }
        DefaultTournamentListView {
            id: tournamentListView
            Layout.fillHeight: true
            Layout.fillWidth: true
            labelTextColor: ThemeContext.manTournamentListViewLabelColor
            onRequestUpdate: ManageScripts.updateTournamentListView()
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
                onClicked: ManageScripts.requestDeleteTournamentPopUp()
            }
        }
    }
    Component.onCompleted: {
        ManageScripts.connectInterface();
        requestPlayers();
    }
    Component.onDestruction: {
        ManageScripts.disconnectInterface();
    }
}
