import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "turn"
import "scores"
import "keyPad"
import "tournamentPageScripts.js" as PageScripts
import "modals"

Page {
        signal menuRequest
        onMenuRequest: dartsController.saveState()

        focus: true
        Keys.onPressed: event => {
                                if (event.key === Qt.Key_Back) {
                                        event.accepted = true
                                        backModal.open()
                                }
                        }

        ColumnLayout {
                anchors.fill: parent
                spacing: 6
                ScoresView {
                        id: scoresView
                        Layout.minimumHeight: 180
                        Layout.maximumHeight: 180
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter
                }

                Text {
                        id: targetRow
                        font.pointSize: 28
                        font.weight: Font.Bold
                        Layout.fillWidth: true
                        Layout.minimumHeight: 28
                        Layout.maximumHeight: 28
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"
                }

                TurnControls {
                        id: turnControls
                        Layout.alignment: Qt.AlignHCenter
                        Layout.minimumHeight: 40
                        Layout.maximumHeight: 40
                        Layout.fillWidth: true
                        onUndoClicked: PageScripts.undo()
                        onRedoClicked: PageScripts.redo()
                        onRestartClicked: restartModal.open()
                        onMenuClicked: menuRequest()
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

        WinnerModal {
                id: winnerModal
                visible: false
                onRestartClicked: PageScripts.restartGame()
                onUndoClicked: PageScripts.undo()
        }

        TextModal {
                id: restartModal
                text: "Sure you want to restart?"
                onAccepted: PageScripts.restartGame()
        }

        TextModal {
                id: backModal
                text: "Sure?"
                onAccepted: menuRequest()
        }

        Component.onCompleted: PageScripts.init()
}
