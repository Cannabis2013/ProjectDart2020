import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "turn"
import "scores"
import "keyPad"
import "scripts/controllerScripts.js" as ControllerScripts
import "scripts/tournamentModals.js" as Modals
import "modals"
import "tournamentPage.js" as Events

Page {
        id: tournamentPage
        signal menuRequest

        focus: true
        Keys.onPressed: event => Events.handleCloseEvent(event)

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
                        onUndoClicked: ControllerScripts.undo()
                        onRedoClicked: ControllerScripts.redo()
                        onRestartClicked: Modals.openRestartModal(ControllerScripts.restartGame)
                        onMenuClicked: menuRequest()
                }

                KeyPads {
                        id: keyPad
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter
                        onReportScore: (modId, point) => ControllerScripts.addScore(modId, point)
                        onBustTurn: value => ControllerScripts.bustScore()
                }
        }

        Component.onCompleted: ControllerScripts.init()
        Component.onDestruction: dartsController.saveState()
}
