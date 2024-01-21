import QtQuick 2.1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "turnControlsSection"
import "scoresSection"
import "inputSection"
import "playersSection"
import "messageSection"
import "statisticsSection"
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
                rows: Scripts.isPortrait() ? 6 : 5

                PlayersSection {
                        id: playersSection
                        Layout.preferredHeight: 66
                        Layout.fillWidth: true
                }

                ScoresSection {
                        id: scoresSection
                        Layout.preferredHeight: 100
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter
                }

                StatisticsSection {
                        id: playerStatistics
                        Layout.preferredHeight: 32
                        Layout.fillWidth: true
                }

                MessageSection {
                        id: messageSection
                        Layout.fillWidth: true
                        Layout.fillHeight: !Scripts.isPortrait()
                        Layout.preferredHeight: 40
                }

                TurnControlsSection {
                        id: turnControls
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
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
                        Layout.rowSpan: Scripts.isPortrait() ? 1 : 5
                        onReportScore: (modId, point) => Scripts.addScore(modId, point)
                        onBustTurn: value => Scripts.bustScore()
                }
        }

        Component.onCompleted: Scripts.init()
        Component.onDestruction: dartsController.saveState()
}
