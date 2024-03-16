import QtQuick 2.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "compTurnControls"
import "compInputs"
import "compMessages"
import "compPlayerInfos"
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

                CompPlayerInfos {
                        id: playerInfos
                        Layout.preferredHeight: 200
                        Layout.fillWidth: true
                }

                CompMessages {
                        id: messageSection
                        Layout.fillWidth: true
                        Layout.fillHeight: !Scripts.isPortrait()
                        Layout.preferredHeight: 64
                }

                CompTurnControls {
                        id: turnControls
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                        Layout.preferredHeight: 32
                        Layout.fillWidth: true
                        onUndoClicked: Scripts.undo()
                        onRedoClicked: Scripts.redo()
                        onRestartClicked: Dialogs.openRestartDialog(Scripts.restartGame)
                }

                CompInputs {
                        id: inputSection
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.rowSpan: Scripts.isPortrait() ? 1 : 3
                        onReportScore: (modId, point) => Scripts.addScore(modId, point)
                        onBustTurn: value => Scripts.bustScore()
                }
        }

        Component.onCompleted: Scripts.initializeUI()
        Component.onDestruction: dartsInitializer.saveState()
}
