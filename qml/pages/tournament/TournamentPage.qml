import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "./turn"
import "./players"
import "./keyPad"
import "./scripts/tournamentPageScripts.js" as PageScripts
import "./header"
import "./modals"

Page {
        signal menuRequest
        onMenuRequest: dartsController.saveState()
        signal restartClicked
        onRestartClicked: restartModal.open()

        GridLayout {
                anchors.fill: parent
                flow: GridLayout.TopToBottom
                rowSpacing: 0

                TournamentHeader {
                        Layout.fillWidth: true
                        Layout.minimumHeight: 40
                        Layout.maximumHeight: 40
                }

                PlayerScores {
                        id: scoresView
                        height: 180
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter
                }

                TurnInformation {
                        id: turnInfoComp
                        Layout.alignment: Qt.AlignHCenter
                        Layout.minimumHeight: 48
                        Layout.maximumHeight: 48
                        Layout.fillWidth: true
                        onUndoClicked: PageScripts.undo()
                        onRedoClicked: PageScripts.redo()
                }

                KeyPads {
                        id: keyPad
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                        onReportScore: (modId, point) => PageScripts.addScore(modId, point)
                        onBustTurn: value => PageScripts.bustScore()
                }
        }

        MediaPlayer {}

        WinnerModal {
                id: winnerModal
                visible: false
                onRestartClicked: PageScripts.restartGame()
                onUndoClicked: PageScripts.undo()
        }

        RestartConfirmation {
                id: restartModal
                onRejected: restartModal.close()
                onAccepted: PageScripts.restartGame()
        }

        Component.onCompleted: PageScripts.init()
}
