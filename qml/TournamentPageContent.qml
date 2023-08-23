import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "tournamentPageScripts.js" as Scripts

Page {
        id: body
        clip: true

        signal backButtonClicked

        header: Button {
                text: qsTr("Back")
                onClicked: backButtonClicked()
        }

        signal createTournamentClicked
        signal dartsPointSingleColumnInitialized
        signal dartsScoreSingleColumnInitialized
        signal manageButtonClicked
        signal requestUpdate

        QtObject {
                id: currentValues
                property int currentIndex: -1
        }
        onRequestUpdate: requestTournaments()
        GridLayout {
                anchors.fill: parent
                columnSpacing: 0
                rowSpacing: 4
                flow: GridLayout.TopToBottom
                TournamentPageListView {
                        id: dartsListView
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        onItemClicked: Scripts.processSelection(index)
                }
                GridLayout {
                        flow: GridLayout.LeftToRight
                        columnSpacing: 2
                        Rectangle {
                                Layout.fillWidth: true
                        }
                        CRUDButton {
                                id: manageButton
                                text: "Manage"
                                onClicked: manageButtonClicked()
                        }
                }
        }
        Component.onCompleted: Scripts.init()
}
