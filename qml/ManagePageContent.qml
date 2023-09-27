import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15

import "./tournaments/listView"
import "./players/listView"

import "managePageScripts.js" as ManageScripts
import "jsPopUpBuilder.js" as PopupBuilder
import "./buttons"

Page {
        id: body
        signal backButtonClicked

        header: Button {
                text: qsTr("Back")
                onClicked: backButtonClicked()
        }

        signal requestCreatePlayerPage
        signal requestCreateTournamentPage

        GridLayout {
                id: mainLayout
                anchors.fill: parent
                flow: GridLayout.TopToBottom
                PlayerListView {
                        id: playersListView
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        onRequestUpdate: ManageScripts.updatePlayerListView()
                }
                GridLayout {
                        id: playerCRUDButtons
                        flow: GridLayout.LeftToRight
                        Rectangle {
                                Layout.fillWidth: true
                        }
                        CRUDButton {
                                text: "Create"
                                onClicked: requestCreatePlayerPage()
                        }
                        CRUDButton {
                                text: "Delete"
                                onClicked: ManageScripts.requestDeletePlayerPopUp()
                        }
                }
                TournamentsView {
                        id: tournamentListView
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        onRequestUpdate: ManageScripts.updateTournamentListView()
                }
                GridLayout {
                        id: tournamentCRUDButtons
                        flow: GridLayout.LeftToRight

                        Rectangle {
                                Layout.fillWidth: true
                        }
                        CRUDButton {
                                text: "Create"
                                onClicked: requestCreateTournamentPage()
                        }
                        CRUDButton {
                                text: "Delete"
                                onClicked: ManageScripts.requestDeleteTournamentPopUp()
                        }
                }
        }
        Component.onCompleted: ManageScripts.init()
}
