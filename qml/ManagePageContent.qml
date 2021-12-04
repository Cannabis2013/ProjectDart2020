import QtQuick 2.12
import QtQuick.Layouts 1.3
import "managePageScripts.js" as ManageScripts
import "jsPopUpBuilder.js" as PopupBuilder
Content {
    id: body
    signal requestCreatePlayerPage
    signal requestCreateTournamentPage
    preferedPageTitle: "Manage"
    GridLayout{
        id: mainLayout
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        DefaultPlayerListView {
            id: playersListView
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
    Component.onCompleted: ManageScripts.init();
}
