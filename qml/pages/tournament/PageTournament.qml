import QtQuick 2.1
import QtQuick.Controls 6.0
import QtQuick.Layouts 1.3
import "turnControls"
import "inputs"
import "messages"
import "players"
import "pageTournament.js" as Scripts
import "dialogs/dialogs.js" as Dialogs

Page {
        id: tournamentPage
        signal menuRequest

        focus: true
        Keys.onPressed: event => Scripts.handleCloseEvent(event)

        GridLayout {
                anchors.fill: parent
                rowSpacing: 0
                columnSpacing: 0
                flow: GridLayout.TopToBottom
                rows: Scripts.isPortrait() ? 4 : 3

                PlayerDisplays {
                        id: playerInfos
                        Layout.preferredHeight: 146
                        Layout.fillWidth: true
                }

                MessagesDisplay {
                        id: messageSection
                        Layout.topMargin: 6
                        Layout.fillWidth: true
                        Layout.fillHeight: !Scripts.isPortrait()
                        Layout.minimumHeight: 48
                        Layout.alignment: Qt.AlignTop
                }

                TurnControls {
                        id: turnControls
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                        Layout.preferredHeight: 36
                        Layout.fillWidth: true
                        Layout.leftMargin: 6
                        Layout.rightMargin: 6
                        onUndoClicked: Scripts.undo()
                        onRedoClicked: Scripts.redo()
                        onRestartClicked: Dialogs.openRestartDialog(Scripts.restartGame)
                }

                CompInputs {
                        id: inputSection
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.minimumWidth: 12
                        Layout.rowSpan: Scripts.isPortrait() ? 1 : 3
                        onReportScores: scores => Scripts.addScore(scores)
                }
        }

        Component.onCompleted: Scripts.initializeUI()
        Component.onDestruction: dartsInitializer.saveState()
}
