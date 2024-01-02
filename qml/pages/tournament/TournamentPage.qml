import QtQuick 2.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "turn"
import "scores"
import "keyPad"
import "modals"
import "scripts/controllerScripts.js" as ControllerScripts
import "scripts/tournamentModals.js" as Modals
import "tournamentPage.js" as Scripts

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
                rows: 4

                ScoresView {
                        id: scoresView
                        Layout.minimumHeight: 180
                        Layout.maximumHeight: 180
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter
                }

                Item {
                        clip: true
                        Layout.fillWidth: true
                        Layout.preferredHeight: 32
                        Text {
                                anchors.fill: parent
                                id: targetRow
                                font.pointSize: 28
                                font.weight: Font.Bold
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                        }
                }

                Item {
                        id: verticalSpacer
                        visible: !Scripts.isPortrait()
                        Layout.fillHeight: true
                        Layout.maximumWidth: 1
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

                KeyPad {
                        id: keyPad
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.rowSpan: Scripts.isPortrait() ? 1 : 4
                        onReportScore: (modId, point) => ControllerScripts.addScore(modId, point)
                        onBustTurn: value => ControllerScripts.bustScore()
                }
        }

        Component.onCompleted: ControllerScripts.init()
        Component.onDestruction: dartsController.saveState()
}
