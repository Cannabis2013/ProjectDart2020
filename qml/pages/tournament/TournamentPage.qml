import QtQuick 2.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "turnControlsSection"
import "scoresSection"
import "inputSection"
import "messageSection"
import "tournamentPage.js" as Scripts
import "textModal/textModal.js" as Modals

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

                ScoresSection {
                        id: scoresSection
                        Layout.minimumHeight: 180
                        Layout.maximumHeight: 180
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter
                }

                MessageSection {
                        id: messageSection
                        Layout.fillWidth: true
                        Layout.preferredHeight: 40
                }

                TurnControlsSection {
                        id: turnControls
                        Layout.alignment: Qt.AlignHCenter
                        Layout.preferredHeight: 32
                        Layout.fillWidth: true
                        onUndoClicked: Scripts.undo()
                        onRedoClicked: Scripts.redo()
                        onRestartClicked: Modals.openRestartModal(Scripts.restartGame)
                }

                PlayerInputSection {
                        id: inputSection
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.rowSpan: Scripts.isPortrait() ? 1 : 4
                        onReportScore: (modId, point) => Scripts.addScore(modId, point)
                        onBustTurn: value => Scripts.bustScore()
                }
        }

        Component.onCompleted: Scripts.init()
        Component.onDestruction: dartsController.saveState()
}
